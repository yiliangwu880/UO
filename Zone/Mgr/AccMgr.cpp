#include "AccMgr.h"
#include "CfgMgr.h"
#include "def.h"
#include "EventMgr.h"
#include "ZoneMgr.h"
#include "Player/Player.h"
#include "UoProto.h"


using namespace std;
using namespace su;
using namespace acc;

namespace
{
	void Start(bool &ret)
	{
		AccMgr::Ins().Start();
	}
	STATIC_RUN(RegEvent<EV_START>(Start))
}

void AccMgr::Start()
{
	L_INFO("ZoneAcc Start");
	std::vector<Addr> vec_addr;
	Addr addr;
	addr.ip = gCfgMgr->ComCfg().access.ip;
	addr.port = gCfgMgr->ComCfg().access.port;
	vec_addr.push_back(addr);
	Init(vec_addr, gCfgMgr->ZoneCfg().svrId);
}

void AccMgr::OnRegResult(uint16 svr_id)
{
	//向acc注册成功
	L_COND_V(svr_id != 0, "reg acc fail");
	L_INFO("zone reg ok");
}


namespace
{


	//Register(0xEF, 21, false, LoginServerSeed);
	void LoginServerSeed(const Session &sn, const PacketReader &pvSrc)
	{
		//int msgSize = pvSrc.ReadUInt16();
		//byte flag = pvSrc.ReadByte();
	}
//	STATIC_RUN(MsgDispatch<const Session>::Ins().RegMsgHandler(&LoginServerSeed));
}

void AccMgr::OnRevClientMsg(const Session &sn, uint32 cmd, const char *msg, uint16 msg_len)
{
	//接收client 请求消息
	L_INFO("echo msg. cmd=%x", cmd);

	//unfinished, 需要改名，不让和svr center 通讯冲突
	MsgDispatch<const Session>::Ins().Dispatch(sn, msg, msg_len);
	//SendToClient(sn.id, cmd, msg, msg_len);
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
	Player *player = AccMgr::Ins().GetPlayer(sn);
	L_COND_V(player);
	player->m_LoginPlayer.ClientDisCon();
}

