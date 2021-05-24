#include "ScenePlayer.h"

void ScenePlayer::State(State val)
{
	State(val);
	if (WaitTranIn == State())
	{
	//	PlayerMgr::Ins().SetCacheMsg(m_owner.Uin(), false);
	}
	else if (Playing == State())
	{
	//	PlayerMgr::Ins().SetCacheMsg(m_owner.Uin(), true);
	}
	else if (WaitReserve == State())
	{
		m_isReserveOk = false;
		m_isAccCacheOk = false;
	}
	else
	{
		L_ERROR("unknow state %d", (int)State());
	}
}


bool ScenePlayer::TranZone(uint16 zoneId, uint32 sceneId)
{
	L_COND_F(Playing == m_State);//传送过程，被动触发传送的情况，先忽略不处理。
	ReqZoneReserve req;
	req.dstZoneId = zoneId;
	req.sceneId = sceneId;
	CenterCon::Ins().Send(req);
	AccMgr::Ins().SetCache(m_owner.Cid(), true);
	m_SceneTran.State(WaitReserve);
}

void ScenePlayer::CheckReserve()
{
	if (m_isAccCacheOk && m_isReserveOk)
	{
		ReqTranZone req;
		req.uin = m_owner.Uin();
		TableCfg::Ins().Pack(m_owner.GetDb(), req.playerData);
		CenterCon::Ins().Send(req);
		PlayerMgr::Ins().Del(m_owner.Uin());
		State(WaitDel);
	}
}

void ScenePlayer::OnMsgRspCacheMsg(bool isCache)
{
	if (isCache)
	{
		L_COND_V(WaitReserve == player->m_SceneTran.m_State);
		m_isAccCacheOk = true;
		CheckReserve();
	}
	else
	{
		L_COND_V(Playing == player->m_SceneTran.m_State);
	}
}

RegCenterMsg(ScenePlayer::ReqZoneReserve);
void ScenePlayer::ReqZoneReserve(ZoneSvrCon &con, const proto::ReqZoneReserve &msg)
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


RegCenterMsg(ScenePlayer::ReqTranZone);
void ScenePlayer::ReqTranZone(ZoneSvrCon &con, const proto::ReqTranZone &msg)
{
	L_INFO("ReqZoneOk_cs");
	Player *player = PlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(WaitTranIn == player->m_SceneTran.m_State);
	PlayerMgr::Ins().SetCacheMsg(msg.uin, false);

	player->m_SceneTran.State(Playing);
}

RegCenterMsg(ScenePlayer::RspZoneReserve);
void ScenePlayer::RspZoneReserve(ZoneSvrCon &con, const proto::RspZoneReserve &msg)
{
	L_INFO("RspZoneReserve");
	Player *player = PlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(WaitReserve == player->m_SceneTran.m_State);
	if (msg.ret)
	{
		m_isReserveOk = true;
		player->m_SceneTran.CheckReserve();
		return;
	}
	else
	{
		L_INFO("reserve fail");
		PlayerMgr::Ins().SetCacheMsg(msg.uin, false);
		player->m_SceneTran.State(Playing);
	}
}