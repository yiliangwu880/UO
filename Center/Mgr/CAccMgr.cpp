#include "CAccMgr.h"
#include "CfgMgr.h"
#include "def.h"
#include "GlobalEvent.h"
#include "CenterMgr.h"
#include "./Account/AccountMgr.h"
#include "MsgDispatch.h"
#include "CenterClientMsgMgr.h"
#include "ComPackets.h"
#include "NetState.h"

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
	addr.ip = gCfgMgr.ComCfg().access.inner_ip;
	addr.port = gCfgMgr.ComCfg().access.inner_port; 
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

void AccMgr::OnRevVerifyReq(const SessionId &id, uint32 cmd, const char *msg, uint16 msg_len)
{
	L_COND_V(CenterMgr::Ins().Allok());
	Session tmpSn;
	tmpSn.id = id;
	PacketHandler *handler = PacketHandlers::Ins().GetHandler(msg[0]);
	L_COND_V(handler, "find msg handler fail. packetId=%d msg_len=%d", (uint8_t)msg[0], msg_len);

	L_DEBUG("rev packetId %x %d, OnRevVerifyReq", (uint8_t)msg[0], msg_len);
	PacketReader r(msg, msg_len, handler->m_Length != 0);
	NetState ns(tmpSn, *this);
	handler->m_OnReceive(ns, r);
}

void AccMgr::OnRevClientMsg(const Session &sn, uint32 cmd, const char *msg, uint16 msg_len)
{
	//L_INFO("OnRevClientMsg.");
	L_COND_V(msg_len > 0);

	PacketHandler *handler = PacketHandlers::Ins().GetHandler(msg[0]);
	L_COND_V(handler, "find msg handler fail. packetId=%d", (uint8_t)msg[0]);

	L_DEBUG("rev packetId %x %d", (uint8_t)msg[0], msg_len);
	PacketReader r(msg, msg_len, handler->m_Length != 0);
	NetState ns(sn, *this);
	handler->m_OnReceive(ns, r);
}

void AccMgr::OnClientConnect(const acc::Session &sn)
{
	L_DEBUG("on client connect。 accName = %s", sn.accName.c_str());
	if (sn.accName.empty())
	{//第一个服务器列表链接通过，不处理
		return;
	}
	Account *acc = AccountMgr::Ins().GetAcc(sn.accName);
	L_COND_V(acc);

	CenterSnEx *p = sn.GetEx<CenterSnEx>();
	L_COND_V(p);
	p->m_pAccount = *acc;

	acc->m_Verify.OnClientConFor2nd(sn.id);
}

void AccMgr::OnRevBroadcastUinToSession(const acc::Session &sn)
{
	//Account *account = AccountMgr::Ins().GetAcc(sn.accName);
	//L_COND_V(account);

	//CenterSnEx *p = sn.GetEx<CenterSnEx>();
	//L_COND_V(p);
	//p->m_pAccount = *account;

	//account->m_Verify.SetVerifyOk(sn.id);
}
