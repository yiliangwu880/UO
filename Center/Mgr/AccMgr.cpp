#include "AccMgr.h"
#include "CfgMgr.h"
#include "def.h"
#include "EventMgr.h"
#include "CenterMgr.h"
#include "./Account/AccountMgr.h"
#include "MsgDispatch.h"
#include "CenterClientMsgMgr.h"
#include "SendToClientMgr.h"

using namespace std;
using namespace su;
using namespace acc;


STATIC_RUN(RegEvent<EV_SVR_START>(AccMgr::Start));
void AccMgr::Start(bool &ret)
{
	L_INFO("centerAD Start");
	{//ACC SETING
		MsgAccSeting set;
		{//初始化所有 cmd 2 grpId. 没设置的cmd 2 默认 zone svr group
			set.defaultGrpId = ZONE_GROUP_ID;
			Cmd2GrpId d;
			d.grpId = CENTER_GROUP_ID;
			for (const PacketHandler &v : PacketHandlers::Ins().GetHandlers())
			{
				if (v.m_PacketID != 0)
				{
					d.vecCmd.push_back(v.m_PacketID);
				}
			}
			set.vecCmd2GrupId.push_back(d);
		}
		AccMgr::Ins().SetAccSeting(set);
	}

	std::vector<Addr> vec_addr;
	Addr addr;
	addr.ip = gCfgMgr->ComCfg().access.ip;
	addr.port = gCfgMgr->ComCfg().access.port;
	vec_addr.push_back(addr);
	AccMgr::Ins().Init(vec_addr, CENTER_GROUP_ID, true);
}

void AccMgr::OnRegResult(uint16 svr_id)
{
	//向acc注册成功
	L_COND_V(svr_id != 0, "reg acc fail");
	L_INFO("center reg ok");
	CenterMgr::Ins().SetCenterOk();
}
namespace
{
	class MobileHitsN : public Packet
	{
	public:
		MobileHitsN() :Packet(0)
		{}

	};
}
void AccMgr::OnRevVerifyReq(const SessionId &id, uint32 cmd, const char *msg, uint16 msg_len)
{
	L_COND_V(CenterMgr::Ins().Allok());
	Session tmpSn;
	tmpSn.id = id;
	PacketHandler *handler = PacketHandlers::Ins().GetHandler(msg[0]);
	if (nullptr == handler)
	{
		L_ERROR("find msg handler fail. packetId=%d", msg[0]);
		return;
	}
	PacketReader r(msg, msg_len, handler->m_Length != 0);
	handler->m_OnReceive(tmpSn, r);

	{
		//无条件认证通过
		VerifyRetStruct d;
		d.is_success = true;
		//d.msg = ntf to client login ok
		AccMgr::Ins().ReqVerifyRet(id, d);
	}

	return;
	{
		L_COND_V(CenterMgr::Ins().Allok());
		size_t len = msg_len;
		proto::Login_cs req;
		L_COND_V(proto::Unpack<proto::Login_cs>(req, msg, len));

		Account *account = AccountMgr::Ins().GetAcc(req.name);
		if (!account)
		{
			account = AccountMgr::Ins().CreateAcc(req.name);
		}
		account->ReqVerify(id, req);
	}
	{//tmp code, 发送到client

		MobileHitsN hitsPacket;
		//Send(id, hitsPacket);
		//AccMgr::Ins().SendToClient
	}

	//临时 接收client请求登录消息,无条件通过，原消息号返回,
	//L_INFO("rev verfiy. cmd=%d", cmd);
	//string s(msg, msg_len);
	//string rsp_msg = "verify_ok";
	//ReqVerifyRet(id, true, cmd, rsp_msg.c_str(), rsp_msg.length());
}

void AccMgr::OnRevClientMsg(const Session &sn, uint32 cmd, const char *msg, uint16 msg_len)
{
	L_INFO("OnRevClientMsg. cmd=%x", cmd);
	L_COND_V(msg_len > 0);

	PacketHandler *handler = PacketHandlers::Ins().GetHandler(msg[0]);
	if (nullptr == handler)
	{
		L_ERROR("find msg handler fail. packetId=%d", msg[0]);
		return;
	}
	PacketReader r(msg, msg_len, handler->m_Length != 0);
	handler->m_OnReceive(sn, r);
}

void AccMgr::OnClientConnect(const acc::Session &sn)
{
	Account *account = AccountMgr::Ins().GetAcc(sn.accName);
	L_COND_V(account);

	CenterSnEx *p = sn.GetEx<CenterSnEx>();
	L_COND_V(p);
	p->m_pAccount = account->GetWeakPtr();

	account->SetVerifyOk(sn.id);
}

void AccMgr::OnRevBroadcastUinToSession(const acc::Session &sn)
{
	Account *account = AccountMgr::Ins().GetAcc(sn.accName);
	L_COND_V(account);

	CenterSnEx *p = sn.GetEx<CenterSnEx>();
	L_COND_V(p);
	p->m_pAccount = account->GetWeakPtr();

	account->SetVerifyOk(sn.id);
}
