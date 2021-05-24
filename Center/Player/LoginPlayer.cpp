#include "LoginPlayer.h"


void LoginPlayer::State(State state)
{

}


void LoginPlayer::LoginZone(const db::Player &data)
{
	L_COND_V(None == m_State);
	proto::ReqLoginZone_sc req;
	TableCfg::Ins().Pack(data, req.playerData);
	m_owner.SendToZone(req);
	m_State = WaitLogin;
}

void LoginPlayer::ReLogin()
{
	L_COND_V(LoginOk == m_State);
	ReqReLoginZone_sc req;
	m_owner.SendToZone(req);
	m_State = WaitReLogin;

}

RegZoneMsg(LoginPlayer::RspLoginZone_cs);
void LoginPlayer::RspLoginZone_cs(ZoneSvrCon &con, const proto::RspLoginZone_cs &msg)
{
	L_INFO("RspLoginZone_cs");
	Player *player = PlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(WaitLogin == player->m_SceneTran.m_State);
	m_State = LoginOk;
}

RegZoneMsg(LoginPlayer::RspReLoginZone_cs);
void LoginPlayer::RspReLoginZone_cs(ZoneSvrCon &con, const proto::RspReLoginZone_cs &msg)
{
	L_INFO("RspReLoginZone_cs");
	Player *player = PlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(WaitReLogin == player->m_SceneTran.m_State);
	m_State = LoginOk;

}
