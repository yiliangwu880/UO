#include "UoClientMsgMgr.h"
#include "external_con.h"
#include "inner_con.h"
#include "com.h"
#include "server.h"
#include "AccMgr.h"
#include "svr_util/include/str_util.h"

using namespace std;
using namespace acc;
using namespace lc;
using namespace su;
ExternalSvrCon::ExternalSvrCon()
	:m_state(State::INIT)
	, m_uin(0)
{
	SetRawReadCb(true);
	//if (0 != CfgMgr::Ins().GetMsbs())
	//{
	//	SetMaxSendBufSize(CfgMgr::Ins().GetMsbs());
	//}
}

ExternalSvrCon::~ExternalSvrCon()
{
	if (IsVerify())
	{
		MsgNtfDiscon ntf;
		ntf.cid = GetId();
		L_ASSERT(ntf.cid);
		const Id2Svr &id_2_svr = RegSvrMgr::Ins().GetRegSvr();
		for (auto &v : id_2_svr)
		{
			InnerSvrCon *p = v.second;
			if (nullptr == p)
			{
				L_ERROR("nullptr == p");
				return;
			}
			p->Send(CMD_NTF_DISCON, ntf);
		}
		L_DEBUG("external client destroy . cid=%llx", GetId());
	}
}

void ExternalSvrCon::SetVerify(bool is_success)
{
	if (m_state != State::WAIT_VERIFY)
	{
		//svr请求验证结果 状态时机不对
		L_WARN("svr req CMD_REQ_VERIFY_RET state not correct");
		return;
	}
	if (is_success)
	{
		m_state = State::VERIFYED;
	}
	else
	{
		m_state = State::INIT;//认证失败，等客户端再次请求认证
	}
	m_verify_tm.StopTimer();
}

bool ExternalSvrCon::IsVerify()
{
	return State::VERIFYED == m_state;
}

bool ExternalSvrCon::SendMsg(const char *msg, uint16 msg_len)
{
	string s;
	s.append(msg, msg_len);
	{
		//L_DEBUG("Send client len=%d, %s", msg_len, StrUtil::BinaryToHex(s).c_str());
		L_DEBUG("Send client len=%d, %x", msg_len, (uint8)msg[0]);
	}
	return SendData(s.c_str(), s.length());
}


void ExternalSvrCon::SetActiveSvrId(uint16 grpId, uint16 svr_id)
{
	L_COND_V(0 != grpId);
	L_COND_V(0 != svr_id);
	L_COND_V(grpId < 100); // groupId用来当数组下标，设计不能过大
	if (m_grpId2SvrId.size() < (size_t)grpId + 1)
	{
		m_grpId2SvrId.resize(grpId + 1);
	}
	m_grpId2SvrId[grpId] = svr_id;
}


void ExternalSvrCon::SetCache(bool isCache)
{
	if (!isCache)//恢复
	{
		for (std::string &str : m_cacheMsg)
		{
			Forward2Svr(str.c_str(), str.length());
		}
		m_cacheMsg.clear();
	}
	m_isCache = isCache;
}


//true 表示 buffer 从4字节读取seed成功 or packetId == 0xEF .
//@cur [in]解包来源内存地址，[out]第一个未解包的内存地址（下个变量解包的内存地址）。
//@len [in]cur有效长度，[out]解包后，cur未使用字节长度
bool ExternalSvrCon::HandleSeed(CPointChar &cur, int &len)
{
	if ((uint8_t)cur[0] == 0xEF)
	{
		// new packet in client	6.0.5.0	replaces the traditional seed method with a	seed packet
		// 0xEF	= 239 =	multicast IP, so this should never appear in a normal seed.	 So	this is	backwards compatible with older	clients.
		Seeded = true;
		return true;
	}

	if (len >= 4)
	{
		const char * m_Peek = cur;

		//buffer.Dequeue(m_Peek, 0, 4);

		uint32 seed = (uint32)((m_Peek[0] << 24) | (m_Peek[1] << 16) | (m_Peek[2] << 8) | m_Peek[3]);
		len -= 4;
		cur += 4;
		if (seed == 0)
		{
			L_ERROR("Login: {0}: Invalid Client");
			DisConnect();
			return false;
		}
		L_DEBUG("HandleSeed get 4 bytes.seed = %d", seed);
		Seed = seed;
		Seeded = true;
		return true;
	}

	return false;
}


bool ExternalSvrCon::CheckEncrypted(uint8_t packetID)
{
	bool SentFirstPacket = m_state == State::VERIFYED;
	if (!SentFirstPacket && packetID != 0xF0 && packetID != 0xF1 && packetID != 0xCF && packetID != 0x80 &&
		packetID != 0x91 && packetID != 0xA4 && packetID != 0xEF && packetID != 0xE4 && packetID != 0xFF)
	{
		L_ERROR("Client: Encrypted Client Unsupported. packetId =%x ", packetID);
		DisConnect();
		return true;
	}

	return false;
}
namespace {

	int GetPacketLength(const char *pMsg, int len)
	{
		if (len >= 3)
		{
			return (pMsg[1] << 8) | pMsg[2];
		}

		return 0;
	}


	unsigned char GetPacketID(const char *m_Buffer, int m_Size)
	{
		if (m_Size >= 1)
		{
			return (unsigned char)m_Buffer[0];
		}

		return (unsigned char)0xFF;
	}

}
//@param pMsg, len  网络缓存字节
//return 返回已经读取的字节数， 0表示包未接收完整。
int ExternalSvrCon::ParsePacket(const char *pMsg, int len, bool &isSeed)
{
	//##接收包格式
	//	前4字节  --seed 作用？
	//		[0] --packetId ，如果包长度固定，通过id 查找 包长度
	//		[1, 2] --如果可变长度包，这里存放包长度。
	//		后面接其他消息内容。 索引从 1或者3（可变长度包）开始
	//抄UO  HandleReceive 函数

		//ByteQueue buffer = ns.Buffer;

	if (pMsg == nullptr || len <= 0)
	{
		L_ERROR("unknow。 pMsg, len= %p %d", pMsg, len);
		return 0;
	}


	if (!Seeded)
	{
		int oldLen = len;
		if (!HandleSeed(pMsg, len))
		{
			L_ERROR("read seed fail");
			return 0;
		}
		int readSeedLen = oldLen - len;
		if (readSeedLen>0)//第二个链接，先读取4字节 seed
		{
			isSeed = true;
			return readSeedLen;
		}
	}

	int length = len; //int length = buffer.Length;

	while (length > 0)
	{
		uint8_t packetID = (uint8_t)GetPacketID(pMsg, len);

		if (CheckEncrypted(packetID))
		{
			return 0;//Encrypted Client Unsupported
		}
		if (0 == packetID)
		{
			L_ERROR("packetID ==0");
			return 0;
		}
		PacketHandler *handler = PacketHandlers::Ins().GetHandler(packetID);
		if (handler == nullptr)
		{
			L_ERROR("find Handler Fail. %x", packetID);
			return 0;
		}

		int packetLength = handler->m_Length;
		if (packetLength <= 0)
		{
			if (length >= 3)
			{
				packetLength = GetPacketLength(pMsg, len);

				if (packetLength < 3)
				{
					L_ERROR("packetLength < 3");
					DisConnect();
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}

		if (length < packetLength)
		{
			return 0;
		}
		L_DEBUG("rev packetID,len=0x%x %d", packetID, packetLength);
		return packetLength ;

	}


	return 0;
}

int ExternalSvrCon::OnRawRecv(const char *pMsg, int len)
{
	L_DEBUG("OnRawRecv msg len = %d", len);
	int totalGetLen = 0;
	for (;;)
	{
		if (len == 0)
		{
			return totalGetLen;
		}
		//分割每个包，交给后续RevPacket处理
		bool isSeed = false;
		int packetLen = ParsePacket(pMsg, len, isSeed);
		if (packetLen == 0)//未接收完整
		{
			return totalGetLen;
		}
		L_COND(packetLen <= len, len);
		if (!isSeed)
		{
			RevPacket(pMsg, packetLen);
		}
		totalGetLen += packetLen;
		pMsg += packetLen;
		len -= packetLen;
	}
}

void ExternalSvrCon::RevPacket(const char *pMsg, int len)
{
	switch (m_state)
	{
	default:
		L_ERROR("unknow state %d", (int)m_state);
		break;
	case ExternalSvrCon::State::INIT:
		Forward2VerifySvr(pMsg, len);
		break;
	case ExternalSvrCon::State::WAIT_VERIFY:
		Forward2VerifySvr(pMsg, len);
		//		L_WARN("client repeated req verify, ignore");
		break;
	case ExternalSvrCon::State::VERIFYED:
		if (m_isCache)
		{
			L_DEBUG("cache msg");
			m_cacheMsg.emplace_back(pMsg, len);
		}
		Forward2Svr(pMsg, len);
		break;
	}
	return;
}

void ExternalSvrCon::OnRecv(const lc::MsgPack &msg)
{
	L_ERROR("unuse");
}

void ExternalSvrCon::OnConnected()
{
	L_DEBUG("OnConnected . client=%s %d. cid=%ld", GetRemoteIp(), GetRemotePort(), GetId());
	const ClientLimitInfo &cli = AccSeting::Ins().m_seting.cli;
	if (Server::Ins().GetExConSize() > cli.max_num)
	{
		L_INFO("external con too much. cur size=%d. rsp_cmd=%d", Server::Ins().GetExConSize(), cli.rsp_cmd);
		SendMsg(cli.rsp_msg.c_str(), cli.rsp_msg.length());
		//延时断开，等上面消息发送出去。这个方法不可靠，可能发送失败。 以后再想办法。
		auto f = std::bind(&ExternalSvrCon::DisConnect, this);
		m_cls_tm.StartTimer(1000, f);
		return;
	}

	if (0 != AccSeting::Ins().m_seting.no_msg_interval_sec)
	{
		//L_DEBUG("start no msg timer . sec=%d", AccSeting::Ins().m_seting.no_msg_interval_sec);
		auto f = std::bind(&ExternalSvrCon::OnWaitFirstMsgTimeOut, this);
		m_wfm_tm.StartTimer(AccSeting::Ins().m_seting.no_msg_interval_sec * 1000, f);
	}
}

//client 接收的tcp pack 转 MsgForward
bool ExternalSvrCon::ClientTcpPack2MsgForward(const lc::MsgPack &msg, MsgForward &f_msg) const
{
	L_COND_F(msg.len >= sizeof(f_msg.cmd));
	f_msg.cid = GetId();
	const char *cur = msg.data;
	f_msg.cmd = *(decltype(f_msg.cmd)*)(cur);
	cur = cur + sizeof(f_msg.cmd);
	f_msg.msg = cur;
	f_msg.msg_len = msg.len - sizeof(f_msg.cmd);
	return true;
}

//client 接收的tcp pack 转 MsgForward
//uo网络格式，其他 游戏需要修改
bool ExternalSvrCon::ClientTcpPack2MsgForward(const char *pMsg, int len, acc::MsgForward &f_msg) const
{
	f_msg.cid = GetId();
	f_msg.cmd = *(uint8_t*)(pMsg);
	f_msg.msg = pMsg;
	f_msg.msg_len = len;
	return true;
}

void ExternalSvrCon::Forward2VerifySvr(const char *pMsg, int len)
{
	//	L_COND_V(State::INIT == m_state); //UO临时不验证

	m_wfm_tm.StopTimer();
	string tcp_pack;
	{//client tcp pack to ASData tcp pack 
		MsgForward f_msg;
		//L_DEBUG("msg.data first 32bit = %x", *(uint32*)msg.data);
		if (!ClientTcpPack2MsgForward(pMsg, len, f_msg))
		{
			L_WARN("client illegal msg");
			return;
		}
		//L_DEBUG("f_msg.cmd = %x", f_msg.cmd);
		L_COND_V(ASMsg::Serialize(CMD_NTF_VERIFY_REQ, f_msg, tcp_pack));
	}

	InnerSvrCon *pSvr = VerifySvrMgr::Ins().GetBLVerifySvr();
	if (nullptr == pSvr)
	{
		L_WARN("can't find verfify svr. maybe you havn't reg your verify svr.");
		DisConnect();
		return;
	}

	pSvr->SendPack(tcp_pack.c_str(), tcp_pack.length());

	m_verify_tm.StopTimer();
	auto f = std::bind(&ExternalSvrCon::OnVerfiyTimeOut, this);
	m_verify_tm.StartTimer(VERIFY_TIME_OUT_SEC * 1000, f);
	m_state = State::WAIT_VERIFY;
}

void ExternalSvrCon::OnVerfiyTimeOut()
{
	L_ASSERT(State::WAIT_VERIFY == m_state);
	L_WARN("wait verify time out, disconnect client");//通常验证服务器异常，导致没验证响应。当连接失败处理
	DisConnect();
}

void ExternalSvrCon::OnHeartbeatTimeOut()
{
	L_DEBUG("OnHeartbeatTimeOut, disconnect client cid=%lld", GetId());
	DisConnect();
}

void ExternalSvrCon::Forward2Svr(const char *pMsg, int len)
{
	MsgForward f_msg;
	if (!ClientTcpPack2MsgForward(pMsg, len, f_msg))
	{
		L_ERROR("client illegal msg");
		return;
	}
	const HeartBeatInfo &hbi = AccSeting::Ins().m_seting.hbi;
	if (hbi.req_cmd != 0 && hbi.req_cmd == f_msg.cmd)
	{//reset heartbeat
		//如果这样做法效率不满意，试下 循环定时器，过期时间里面检查心跳状态是否没更新，没更新就断开。 这样让用户层不用创建销毁定时器。
		m_heartbeat_tm.StopTimer();
		L_ASSERT(0 != hbi.interval_sec);
		auto f = std::bind(&ExternalSvrCon::OnHeartbeatTimeOut, this);
		L_DEBUG("rev beat, start time sec=%d", hbi.interval_sec);
		m_heartbeat_tm.StartTimer(hbi.interval_sec * 1000, f);
		SendMsg("a", 0);//unfinished
		return;
	}
	//真正处理转发
	//s1:cmd 找 groupId,找不到转发到缺省组. end
	//s2:groupId 找 svrId,找不到转发到svrId==groupId
	//end
	uint16 cmd = (uint8_t)f_msg.msg[0]; //UO 获取第一个字节为消息号
	uint16 svr_id = 0;
	{//get svr_id
		auto it = g_AccSeting->m_cmd2GrpId.find(cmd);
		if (it == g_AccSeting->m_cmd2GrpId.end())
		{
			svr_id = g_AccSeting->m_seting.defaultGrpId;
		}
		else
		{
			uint16 grpId = it->second;
			if (m_grpId2SvrId.size() >= (size_t)grpId + 1)
			{
				svr_id = m_grpId2SvrId[grpId];
			}
			if (0 == svr_id)
			{
				svr_id = grpId;
			}
		}
	}
	if (0 == svr_id)
	{
		L_ERROR("invaild cmd %x. hight uint16 must can't be 0", f_msg.cmd);
		DisConnect();
		return;
	}

	//L_DEBUG("f_msg.cmd=%x HeartbeatInfo::Ins().cmd=%x %x", f_msg.cmd, AccSeting::Ins().m_seting.hbi.req_cmd, AccSeting::Ins().m_seting.hbi.rsp_cmd);
	InnerSvrCon *pSvr = RegSvrMgr::Ins().Find(svr_id);
	if (nullptr == pSvr)
	{
		L_WARN("client req can't find svr. cmd=%x svr_id=%d main_cmd=%d", f_msg.cmd, svr_id, cmd);
		return;
	}
	if (!pSvr->IsReg())
	{
		L_WARN("client req find svr, but not reg ok. cmd=%x svr_id=%d main_cmd=%d", f_msg.cmd, svr_id, cmd);
		return;
	}

	string tcp_pack;
	L_COND_V(ASMsg::Serialize(CMD_NTF_FORWARD, f_msg, tcp_pack));
	pSvr->SendPack(tcp_pack.c_str(), tcp_pack.length());

}

void ExternalSvrCon::OnWaitFirstMsgTimeOut()
{
	L_INFO("wait client 1st msg time out, disconnect");
	DisConnect();
}

