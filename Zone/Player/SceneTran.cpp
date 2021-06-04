#include "PlayerMgr.h"

using namespace proto;



bool SceneTran::TranZone(uint16 zoneId, uint32 sceneId)
{
	L_COND_F(Playing == m_State);//传送过程，被动触发传送的情况，先忽略不处理。
	proto::ReqZoneReserve req;
	req.dstZoneId = zoneId;
	req.sceneId = sceneId;
	CenterCon::Ins().Send(req);
	AccMgr::Ins().SetCache(m_owner.m_PlayerSn.GetSid(), true);
	m_isReserveOk = false;
	m_isAccCacheOk = false;
	m_State =WaitReserve;
	return true;
}

void SceneTran::CheckReserve()
{
	if (m_isAccCacheOk && m_isReserveOk)
	{
		proto::ReqTranZone req;
		req.uin = m_owner.Uin();
		TableCfg::Ins().Pack(m_owner.m_PlayerDb.GetData(), req.playerData);
		CenterCon::Ins().Send(req);
		PlayerMgr::Ins().DelPlayer(m_owner.Uin());
		State(WaitDel);
	}
}

void SceneTran::OnMsgRspCacheMsg(bool isCache)
{
	if (isCache)
	{
		L_COND_V(WaitReserve == m_State);
		m_isAccCacheOk = true;
		CheckReserve();
	}
	else
	{
		L_COND_V(Playing == m_State);
	}
}

RegCenterMsg(SceneTran::ReqZoneReserve);
void SceneTran::ReqZoneReserve(CenterCon &con, const proto::ReqZoneReserve &msg)
{
	proto::RspZoneReserve rsp;
	Player *player = PlayerMgr::Ins().CreatePlayer(msg.uin, "");
	if (nullptr == player)
	{
		rsp.ret = false;
		con.Send(rsp);
	}
	player->m_SceneTran.m_State =WaitTranIn;

	rsp.ret = true;
	con.Send(rsp);
}


RegCenterMsg(SceneTran::ReqTranZone);
void SceneTran::ReqTranZone(CenterCon &con, const proto::ReqTranZone &msg)
{
	L_INFO("ReqTranZone");
	Player *player = PlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(WaitTranIn == player->m_SceneTran.m_State);

	AccMgr::Ins().SetCache(player->m_PlayerSn.GetSid(), false);

	player->m_SceneTran.m_State= Playing;
}

RegCenterMsg(SceneTran::RspZoneReserve);
void SceneTran::RspZoneReserve(CenterCon &con, const proto::RspZoneReserve &msg)
{
	L_INFO("RspZoneReserve");
	Player *player = PlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(WaitReserve == player->m_SceneTran.m_State);
	if (msg.ret)
	{
		player->m_SceneTran.m_isReserveOk = true;
		player->m_SceneTran.CheckReserve();
		return;
	}
	else
	{
		L_INFO("reserve fail");
		AccMgr::Ins().SetCache(player->m_PlayerSn.GetSid(), false);
		player->m_SceneTran.m_State = Playing;
	}
}