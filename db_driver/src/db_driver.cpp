
#include "db_driver.h"
#include "log_def.h"
#include "connect.h"
#include "libevent_cpp/include/include_all.h"
#include "svr_util/include/stl_boost.h"

using namespace std;
using namespace lc;
using namespace su;
using namespace db;

namespace
{
	//�� BaseTable���� �� Э��ṹProtoType  ������ MsgPack,������MsgPack::len��ProtoType �����ֶ�����δ��ֵ��
	//��������Ľṹ��dataLen data[0]��������壬���db ����
	//	struct query_sc
	//{
	//	const uint16_t id = 6;
	//	bool ret;  //��������
	//  uint32_t dataLen;
	//	char data[0]; //һ��db ����
	//};
	template<class ProtoType>
	ProtoType *BuildMsgPack(MsgPack &msg, const db::BaseTable &data)
	{
		//Ҫ��dataLen data[0]���������
		static_assert((size_t)&(((ProtoType *)(nullptr))->dataLen) == sizeof(ProtoType)-sizeof(uint32_t));
		static_assert((size_t)&(((ProtoType *)(nullptr))->data) == sizeof(ProtoType));
		static_assert((size_t)&(((ProtoType *)(nullptr))->id) == 0); //id�������ȶ���

		ProtoType *p = new (msg.data)ProtoType;
		//data���ó���
		size_t len = ArrayLen(msg.data) - sizeof(*p);
		if (!TableCfg::Ins().Pack(data, p->data, len))		{
			L_ERROR("pack fail");			return nullptr;		}		p->dataLen = len;		msg.len = sizeof(ProtoType) + len;		return p;	}
}

db::Dbproxy::Dbproxy()
{
	RegProtoParse(ParseInsert);
	RegProtoParse(ParseQuery);
	RegProtoParse(ParseDel);
	RegProtoParse(ParseExcuteSql);
}

namespace
{
	template<class M>
	void Check(M &m_sid2QuerySn)
	{
		std::vector<uint16_t> vecSid;
		time_t now = time(nullptr);
		for (auto &v : m_sid2QuerySn)
		{
			const Session &sn = v.second;
			if (sn.m_time - now > 30)
			{
				vecSid.push_back(v.first);
			}
		}
		for (auto &id : vecSid)
		{
			m_sid2QuerySn.erase(id);
		}
	}
}
void db::Dbproxy::OnCheckSession()
{
	Check(m_sid2Sn);

}

void db::Dbproxy::Init(const std::string &ip, uint16_t port, ConCb cb, ExcuteSqlCb sqlCb)
{
	DbClientCon::Ins().ConnectInit(ip.c_str(), port);
	m_conCb = cb;
	m_sqlCb = sqlCb;

	lc::Timer tm;
	m_tm.StartTimerSec(30, std::bind(&Dbproxy::OnCheckSession, this), true);
}

bool db::Dbproxy::Insert(const db::BaseTable &data, any para)
{
	m_sidSeed++;
	Session sn;
	sn.para = para;
	m_sid2Sn.emplace(make_pair(m_sidSeed, sn));

	MsgPack msg;
	auto p = BuildMsgPack<insert_cs>(msg, data);
	L_COND(p, false);
	p->sid = m_sidSeed;
	return DbClientCon::Ins().SendData(msg);
}

bool db::Dbproxy::Update(const db::BaseTable &data)
{
	MsgPack msg;
	auto p = BuildMsgPack<update_cs>(msg, data);
	L_COND(p, false);
	return DbClientCon::Ins().SendData(msg);
}

bool db::Dbproxy::Query(const db::BaseTable &data, any para, uint32 limit_num /*= 1*/)
{
	m_sidSeed++;
	Session sn;
	sn.para = para;
	m_sid2Sn.emplace(make_pair(m_sidSeed, sn));

	MsgPack msg;
	auto req = BuildMsgPack<query_cs>(msg, data);
	L_COND(req, false);
	req->sid = m_sidSeed;
	req->isStr = false;
	req->limit_num = limit_num;
	return DbClientCon::Ins().SendData(msg);
}

bool db::Dbproxy::Query(const db::BaseTable &data, const std::string &cond, any para, uint32 limit_num /*= 1*/)
{
	m_sidSeed++;
	Session sn;
	sn.para = para;
	m_sid2Sn.emplace(make_pair(m_sidSeed, sn));

	MsgPack msg;
	query_cs *req = new (msg.data)query_cs;
	req->sid = m_sidSeed;
	req->limit_num = limit_num;
	req->isStr = true;
	req->table_id = data.TableId();
	L_COND(cond.length() + sizeof(*req) < sizeof(msg.data), false);	req->dataLen = cond.length();	memcpy(req->data, cond.c_str(), cond.length());	msg.len = sizeof(*req) + req->dataLen;
	return DbClientCon::Ins().SendData(msg);
}

bool db::Dbproxy::Del(const db::BaseTable &data, any para)
{
	m_sidSeed++;
	Session sn;
	sn.para = para;
	m_sid2Sn.emplace(make_pair(m_sidSeed, sn));
	MsgPack msg;
	auto p = BuildMsgPack<del_cs>(msg, data);
	L_COND(p, false);
	p->sid = m_sidSeed;
	return DbClientCon::Ins().SendData(msg);
}

void db::Dbproxy::ExecuteSql(const std::string &sql, uint32_t sql_id)
{
	MsgPack msg;
	excute_sql_cs *req = new (msg.data)excute_sql_cs;	req->sql_id = sql_id;	L_COND_V(sql.length() + sizeof(*req) < sizeof(msg.data));	req->dataLen = sql.length();	memcpy(req->data, sql.c_str(), sql.length());	msg.len = sizeof(*req) + req->dataLen;
	DbClientCon::Ins().SendData(msg);
}

void db::Dbproxy::OnRecv(const lc::MsgPack &msg)
{
	using ComFun = void(const char &); //��Ϣ�ص������� �������͡� 
	uint16_t cmdId = *(const uint16_t *)msg.data; //Լ��Э��ǰ uint16_t Ϊ cmdId. ���� 
	auto it = m_cmdId2Cb.find(cmdId);
	if (it == m_cmdId2Cb.end())
	{
		L_ERROR("unknow cmdId %d", cmdId);
		return;
	}
	ComFun *fun = (ComFun *)it->second; 
	const char *pMsg = &(msg.data[0]);
	(*fun)(*pMsg);
}

void db::Dbproxy::ParseInsert(const insert_sc &msg)
{
	std::unique_ptr<BaseTable> pTable = TableCfg::Ins().Unpack(msg.data, msg.dataLen);
	L_COND_V(nullptr != pTable);

	using ComFun = void(bool, const BaseTable&, std::any); //��ѯ�ص��� �������͡� 
	ComFun **fun = (ComFun **)(su::MapFind(Dbproxy::Ins().m_id2InertCb, pTable->TableId()));
	if (nullptr == fun)
	{
		return;
	}
	
	auto it = Dbproxy::Ins().m_sid2Sn.find(msg.sid);
	L_COND_V(it != Dbproxy::Ins().m_sid2Sn.end());
	(**fun)(msg.ret, *(pTable.get()), (it->second).para);
	Dbproxy::Ins().m_sid2Sn.erase(it);
}

void db::Dbproxy::ParseQuery(const query_sc &msg)
{
	std::unique_ptr<BaseTable> pTable = TableCfg::Ins().Unpack(msg.data, msg.dataLen);
	L_COND_V(nullptr != pTable);

	using ComFun = void(bool, const BaseTable&, std::any); //��ѯ�ص��� �������͡� 
	ComFun **fun = (ComFun **)(su::MapFind(Dbproxy::Ins().m_id2QueryCb, pTable->TableId()));
	if (nullptr == fun)
	{
		return;
	}
	auto it = Dbproxy::Ins().m_sid2Sn.find(msg.sid);
	L_COND_V(it != Dbproxy::Ins().m_sid2Sn.end());
	(**fun)(msg.ret, *(pTable.get()), (it->second).para);
	Dbproxy::Ins().m_sid2Sn.erase(it);
}



void db::Dbproxy::ParseDel(const del_sc &msg)
{
	std::unique_ptr<BaseTable> pTable = TableCfg::Ins().Unpack(msg.data, msg.dataLen);
	L_COND_V(nullptr != pTable);

	using ComFun = void(bool, const BaseTable&, std::any); //��ѯ�ص��� �������͡� 
	ComFun **fun = (ComFun **)(su::MapFind(Dbproxy::Ins().m_id2DelCb, pTable->TableId()));
	if (nullptr == fun)
	{
		return;
	}
	auto it = Dbproxy::Ins().m_sid2Sn.find(msg.sid);
	L_COND_V(it != Dbproxy::Ins().m_sid2Sn.end());
	(**fun)(msg.ret, *(pTable.get()), (it->second).para);
	Dbproxy::Ins().m_sid2Sn.erase(it);
}

void db::Dbproxy::ParseExcuteSql(const excute_sql_sc &msg)
{
	if (Dbproxy::Ins().m_sqlCb)
	{
		Dbproxy::Ins().m_sqlCb(msg.sql_id);
	}
}
