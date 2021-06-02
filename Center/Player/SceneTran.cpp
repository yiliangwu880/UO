#include "CPlayerMgr.h"
#include "svr_util/include/static_reg.h"

void SceneTran::SetState(State val)
{
	if (Playing == m_State)
	{
		CPlayerMgr::Ins().SetCacheMsg(m_owner.Uin(), false);
	}
	else if (Moving == m_State)
	{
		CPlayerMgr::Ins().SetCacheMsg(m_owner.Uin(), true);
	}
	else
	{
		L_ERROR("unknow state %d", (int)m_State);
	}
	m_State = val;
}



RegZoneMsg(SceneTran::ReqZoneReserve);
void SceneTran::ReqZoneReserve(ZoneSvrCon &con, const proto::ReqZoneReserve &msg)
{
	CPlayer *player = CPlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(Playing == player->m_SceneTran.m_State);
	ZoneSvr *svr = ZoneSvrMgr::Ins().FindZoneSvr(msg.dstZoneId);
	svr->Send(msg);
}

RegZoneMsg(SceneTran::RspZoneReserve);
void SceneTran::RspZoneReserve(ZoneSvrCon &con, const proto::RspZoneReserve &msg)
{
	CPlayer *player = CPlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(Playing == player->m_SceneTran.m_State);
	ZoneSvr *svr = ZoneSvrMgr::Ins().FindZoneSvr(msg.srcZoneId);
	svr->Send(msg);
	if (msg.ret)
	{
		player->m_SceneTran.SetState(Moving);
	} 
}

RegZoneMsg(SceneTran::ReqTranZone);
void SceneTran::ReqTranZone(ZoneSvrCon &con, const proto::ReqTranZone &msg)
{
	CPlayer *player = CPlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(Moving == player->m_SceneTran.m_State);
	ZoneSvr *svr = ZoneSvrMgr::Ins().FindZoneSvr(msg.zoneId);
	svr->Send(msg);
	player->m_SceneTran.SetState(Playing);
}
