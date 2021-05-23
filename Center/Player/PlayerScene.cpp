#include "PlayerScene.h"
//µÄ¿´·¨
void PlayerScene::State(State val)
{
	State(val);
	if (State::Playing == State())
	{
		PlayerMgr::Ins().SetCacheMsg(m_owner.Uin(), false);
	}
	else if (State::Moving == State())
	{
		PlayerMgr::Ins().SetCacheMsg(m_owner.Uin(), true);
	}
	else
	{
		L_ERROR("unknow state %d", (int)State());
	}
}

RegZoneMsg(PlayerScene::RspLoginZone_cs);
void PlayerScene::RspLoginZone_cs(ZoneSvrCon &con, const proto::RspLoginZone_cs &msg)
{
	L_INFO("ReqZoneOk_cs");
	Player *player = PlayerMgr::Ins().GetPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(Playing == player->m_SceneTran.m_State);

	if (State::Playing == State())
	{
		//resume msg
	}
	else if (State::Moving == State())
	{
		//pause msg
	}
	else if (State::WaitEnterZone == State())
	{
		State(Playing);
	}
	else
	{
		L_ERROR("unknow state %d", (int)State());
	}
}

RegZoneMsg(PlayerScene::ReqZoneReserve);
void PlayerScene::ReqZoneReserve(ZoneSvrCon &con, const proto::ReqZoneReserve &msg)
{
	Player *player = PlayerMgr::Ins().GetPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(Playing == player->m_SceneTran.m_State);
	ZoneSvr *svr = ZoneSvrMgr::FindZoneSvr(msg.dstZoneId);
	svr->Send(msg);
}

RegZoneMsg(PlayerScene::RspZoneReserve);
void PlayerScene::RspZoneReserve(ZoneSvrCon &con, const proto::RspZoneReserve &msg)
{
	Player *player = PlayerMgr::Ins().GetPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(Playing == player->m_SceneTran.m_State);
	ZoneSvr *svr = ZoneSvrMgr::FindZoneSvr(msg.srcZoneId);
	svr->Send(msg);
	if (msg.ret)
	{
		SetState(Moving);
	} 
}

RegZoneMsg(PlayerScene::ReqTranZone);
void PlayerScene::ReqTranZone(ZoneSvrCon &con, const proto::ReqTranZone &msg)
{
	Player *player = PlayerMgr::Ins().GetPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(Moving == player->m_SceneTran.m_State);
	ZoneSvr *svr = ZoneSvrMgr::FindZoneSvr(msg.zoneId);
	svr->Send(msg);
	if (msg.ret)
	{
		player->m_SceneTran.SetState(Playing);
	}

}
