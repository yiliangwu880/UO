#include "CPlayerMgr.h"

using namespace proto;


void LoginPlayer::SetState(State state)
{

}


void LoginPlayer::LoginZone(const DbPlayer &data, bool isCreate)
{
	L_COND_V(None == m_State);
	proto::ReqLoginZone_sc req;
	req.isCreate = isCreate;
	req.cid = m_owner.m_CPlayerSn.GetSid().cid;
	db::TableCfg::Ins().Pack(data, req.playerData);
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
	CPlayer *player = CPlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(WaitLogin == player->m_LoginPlayer.m_State);
	player->m_LoginPlayer.m_State = LoginOk;
}

RegZoneMsg(LoginPlayer::RspReLoginZone_cs);
void LoginPlayer::RspReLoginZone_cs(ZoneSvrCon &con, const proto::RspReLoginZone_cs &msg)
{
	L_INFO("RspReLoginZone_cs");
	CPlayer *player = CPlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(WaitReLogin == player->m_LoginPlayer.m_State);
	player->m_LoginPlayer.m_State = LoginOk;

}
