#include "eventMgr.h"
#include "db_driver.h"
#include "Proto1.h"
#include "ProtoMgr.h"

using namespace std;
using namespace su;

void f1(const proto::insert_sc &msg)
{
	
}

void testStart()
{
	L_INFO("test start");

	db::Dbproxy::Ins().Init("abc", 11);
	proto::ProtoMgr::Ins().RegMsgHandler(f1);
	 
}


STATIC_RUN(RegEvent<EV_CFG_INI>(testStart))

/////////////acc driver//////
#include "acc_driver.h"
#define UNIT_INFO L_INFO
using namespace std;
using namespace su;
using namespace lc;
using namespace acc;

class EchoServer : public ADFacadeMgr
{
public:
	EchoServer()
	{
	}
	void Start();
	virtual void OnRegResult(uint16 svr_id);
	virtual void OnRevVerifyReq(const SessionId &id, uint32 cmd, const char *msg, uint16 msg_len);
	virtual void OnRevClientMsg(const Session &session, uint32 cmd, const char *msg, uint16 msg_len);
};

void EchoServer::Start()
{
	UNIT_INFO("EchoServer Start");
	std::vector<Addr> vec_addr;
	Addr addr;
	addr.ip = "127.0.0.1";
	addr.port = 54831;//���� acc�ڲ���ַ
	vec_addr.push_back(addr);
	Init(vec_addr, 1, true);
}

void EchoServer::OnRegResult(uint16 svr_id)
{
	//��accע��ɹ�
	UNIT_INFO("EchoServer reg ok");
}

void EchoServer::OnRevVerifyReq(const SessionId &id, uint32 cmd, const char *msg, uint16 msg_len)
{
	//����client�����¼��Ϣ,������ͨ����ԭ��Ϣ�ŷ���
	UNIT_INFO("rev verfiy. cmd=%d", cmd);
	string s(msg, msg_len);
	string rsp_msg = "verify_ok";
	ReqVerifyRet(id, true, cmd, rsp_msg.c_str(), rsp_msg.length());
}

void EchoServer::OnRevClientMsg(const Session &session, uint32 cmd, const char *msg, uint16 msg_len)
{
	//����client ������Ϣ
	UNIT_INFO("echo msg. cmd=%x", cmd);
	SendToClient(session.id, cmd, msg, msg_len);
}

void testAcc()
{

	EchoServer svr;
	svr.Start();


}


STATIC_RUN(RegEvent<EV_CFG_INI>(testAcc))