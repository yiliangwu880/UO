#include "AccMgr.h"
#include "CfgMgr.h"
#include "GlobalEvent.h"
#include "ZoneMgr.h"
#include "Player/Player.h"
#include "UoProto.h"
#include "ZoneClientMsgMgr.h"
#include "NetState.h"


using namespace std;
using namespace su;
using namespace acc;



STATIC_RUN(RegEvent<EV_SVR_START>(AccMgr::Start));
void AccMgr::Start(bool &ret)
{
	L_INFO("ZoneAcc Start");
	std::vector<Addr> vec_addr;
	Addr addr;
	addr.ip = gCfgMgr.ComCfg().access.inner_ip;
	addr.port = gCfgMgr.ComCfg().access.inner_port;
	vec_addr.push_back(addr);

	L_ASSERT(gCfgMgr.ZoneCfg().svrId >= ZONE_GROUP_ID && gCfgMgr.ZoneCfg().svrId <= MAX_ZONE_GROUP_ID);
	AccMgr::Ins().Init(vec_addr, gCfgMgr.ZoneCfg().svrId);
}

void AccMgr::OnRegResult(uint16 svr_id)
{
	//向acc注册成功
	L_COND_V(svr_id != 0, "reg acc fail");
	L_INFO("zone reg ok");
}



//接收client 请求消息
void AccMgr::OnRevClientMsg(const Session &sn, uint32 cmd, const char *msg, uint16 msg_len)
{
	L_INFO("OnRevClientMsg. cmd=%x", cmd);
	L_COND_V(msg_len > 0);

	PacketHandler *handler = PacketHandlers::Ins().GetHandler(msg[0]);
	L_COND_V(handler, "find msg handler fail. packetId=%x", (uint8)msg[0]);

	L_DEBUG("rev packetId %x", (uint8_t)msg[0]);
	PacketReader r(msg, msg_len, handler->m_Length != 0);
	NetState ns(sn, *this);
	handler->m_OnReceive(ns, r);
}

Player *AccMgr::GetPlayer(const acc::Session &sn)
{
	WeakPlayer *p = sn.GetEx<WeakPlayer>();
	L_COND(p, nullptr);
	shared_ptr<Player> player = p->lock();
	return player.get();
}

void AccMgr::OnMsgRspCacheMsg(const acc::Session &sn, bool isCache)
{
	Player *player = AccMgr::Ins().GetPlayer(sn);
	L_COND_V(player);
	player->m_SceneTran.OnMsgRspCacheMsg(isCache);
}

void AccMgr::OnClientDisCon(const acc::Session &sn)
{
	//Player *player = AccMgr::Ins().GetPlayer(sn);
	//L_COND_V(player);
	//player->m_LoginPlayer.ClientDisCon();
}

void AccMgr::OnRevBroadcastUinToSession(const acc::Session &session)
{

}

