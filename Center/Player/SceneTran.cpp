#include "SceneTran.h"

void SceneTran::State(State val)
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



RegZoneMsg(SceneTran::ReqZoneReserve);
void SceneTran::ReqZoneReserve(ZoneSvrCon &con, const proto::ReqZoneReserve &msg)
{
	Player *player = PlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(Playing == player->m_SceneTran.m_State);
	ZoneSvr *svr = ZoneSvrMgr::FindZoneSvr(msg.dstZoneId);
	svr->Send(msg);
}

RegZoneMsg(SceneTran::RspZoneReserve);
void SceneTran::RspZoneReserve(ZoneSvrCon &con, const proto::RspZoneReserve &msg)
{
	Player *player = PlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(Playing == player->m_SceneTran.m_State);
	ZoneSvr *svr = ZoneSvrMgr::FindZoneSvr(msg.srcZoneId);
	svr->Send(msg);
	if (msg.ret)
	{
		SetState(Moving);
	} 
}

RegZoneMsg(SceneTran::ReqTranZone);
void SceneTran::ReqTranZone(ZoneSvrCon &con, const proto::ReqTranZone &msg)
{
	Player *player = PlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(Moving == player->m_SceneTran.m_State);
	ZoneSvr *svr = ZoneSvrMgr::FindZoneSvr(msg.zoneId);
	svr->Send(msg);
	if (msg.ret)
	{
		player->m_SceneTran.SetState(Playing);
	}

}
