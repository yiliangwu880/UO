#include "PlayerScene.h"
//µÄ¿´·¨
void PlayerScene::State(State val)
{
	State(val);
	if (State::Playing == State())
	{
	//	PlayerMgr::Ins().SetCacheMsg(m_owner.Uin(), false);
	}
	else if (State::Moving == State())
	{
	//	PlayerMgr::Ins().SetCacheMsg(m_owner.Uin(), true);
	}
	else
	{
		L_ERROR("unknow state %d", (int)State());
	}
}


bool PlayerScene::TranZone(uint16 zoneId, uint32 sceneId)
{
	L_COND_F(Playing == m_State);
	ReqZoneReserve req;
	req.dstZoneId = zoneId;
	req.sceneId = sceneId;
	CenterCon::Ins().Send(req);
	AccMgr::Ins().SetCache(m_owner.Cid(), true);
	m_SceneTran.State(WaitReserve);
}

RegZoneMsg(PlayerScene::ReqZoneReserve);
void PlayerScene::ReqZoneReserve(ZoneSvrCon &con, const proto::ReqZoneReserve &msg)
{
	RspZoneReserve rsp;
	Player *player = PlayerMgr::Ins().CreatePlayer(msg.uin);
	if (nullptr == player)
	{
		rsp.ret = false;
		con.Send(rsp);
	}
	player->m_SceneTran.State(WaitTranIn);

	rsp.ret = true;
	con.Send(rsp);
}


RegZoneMsg(PlayerScene::ReqTranZone);
void PlayerScene::ReqTranZone(ZoneSvrCon &con, const proto::ReqTranZone &msg)
{
	L_INFO("ReqZoneOk_cs");
	Player *player = PlayerMgr::Ins().GetPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(WaitTranIn == player->m_SceneTran.m_State);
	PlayerMgr::Ins().SetCacheMsg(msg.uin, false);

	player->m_SceneTran.State(Playing);


}