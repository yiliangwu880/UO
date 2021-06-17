#include "PlayerMgrC.h"

using namespace proto;


void LoginPlayerC::SetState(State state)
{

}


void LoginPlayerC::LoginZone(const DbPlayer &data, bool isCreate)
{
	L_COND_V(None == m_State);
	proto::ReqLoginZone_sc req;
	req.isCreate = isCreate;
	req.cid = m_owner.m_CPlayerSn.GetSid().cid;
	db::TableCfg::Ins().Pack(data, req.playerData);
	m_owner.SendToZone(req);
	m_State = WaitLogin;
}

void LoginPlayerC::ReLogin()
{
	L_COND_V(LoginOk == m_State);
	ReqReLoginZone_sc req;
	req.cid = m_owner.m_CPlayerSn.GetSid().cid;
	req.uin = m_owner.Uin();
	m_owner.SendToZone(req);
	m_State = WaitReLogin;

}

RegZoneMsg(LoginPlayerC::RspLoginZone_cs);
void LoginPlayerC::RspLoginZone_cs(ZoneSvrCon &con, const proto::RspLoginZone_cs &msg)
{
	L_INFO("RspLoginZone_cs");
	PlayerC *player = PlayerMgrC::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(WaitLogin == player->m_LoginPlayer.m_State);
	player->m_LoginPlayer.m_State = LoginOk;
}

RegZoneMsg(LoginPlayerC::RspReLoginZone_cs);
void LoginPlayerC::RspReLoginZone_cs(ZoneSvrCon &con, const proto::RspReLoginZone_cs &msg)
{
	L_INFO("RspReLoginZone_cs");
	PlayerC *player = PlayerMgrC::Ins().FindPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(WaitReLogin == player->m_LoginPlayer.m_State);
	player->m_LoginPlayer.m_State = LoginOk;

}
