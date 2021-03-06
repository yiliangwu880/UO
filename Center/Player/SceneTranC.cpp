#include "PlayerMgrC.h"
#include "svr_util/include/static_reg.h"



void SceneTranC::SetState(State val)
{
	if (Playing == m_State)
	{
		PlayerMgrC::Ins().SetCacheMsg(m_owner.Uin(), false);
	}
	else if (Moving == m_State)
	{
		PlayerMgrC::Ins().SetCacheMsg(m_owner.Uin(), true);
	}
	else
	{
		L_ERROR("unknow state %d", (int)m_State);
	}
	m_State = val;
}



RegZoneMsg(SceneTranC::ReqZoneReserve);
void SceneTranC::ReqZoneReserve(ZoneSvrCon &con, const proto::ReqZoneReserve &msg)
{
	PlayerC *player = PlayerMgrC::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(Playing == player->m_SceneTran.m_State);
	ZoneSvr *svr = ZoneSvrMgr::Ins().FindZoneSvr(msg.dstZoneId);
	svr->Send(msg);
}

RegZoneMsg(SceneTranC::RspZoneReserve);
void SceneTranC::RspZoneReserve(ZoneSvrCon &con, const proto::RspZoneReserve &msg)
{
	PlayerC *player = PlayerMgrC::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(Playing == player->m_SceneTran.m_State);
	ZoneSvr *svr = ZoneSvrMgr::Ins().FindZoneSvr(msg.srcZoneId);
	svr->Send(msg);
	if (msg.ret)
	{
		player->m_SceneTran.SetState(Moving);
	} 
}

RegZoneMsg(SceneTranC::ReqTranZone);
void SceneTranC::ReqTranZone(ZoneSvrCon &con, const proto::ReqTranZone &msg)
{
	PlayerC *player = PlayerMgrC::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(Moving == player->m_SceneTran.m_State);
	ZoneSvr *svr = ZoneSvrMgr::Ins().FindZoneSvr(msg.zoneId);
	svr->Send(msg);
	player->m_SceneTran.SetState(Playing);
}
