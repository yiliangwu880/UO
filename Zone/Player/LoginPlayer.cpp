#include "LoginPlayer.h"




RegCenterMsg(LoginPlayer::ReqLoginZone_sc);

void LoginPlayer::LoginZone(const db::Player &data)
{
	proto::ReqLoginZone_sc
}

void LoginPlayer::ClientDisCon()
{
	L_COND_V(LoginOk == m_State);
	m_State = OffLine;
}

void LoginPlayer::ReqLoginZone_sc(ZoneSvrCon &con, const proto::ReqLoginZone_sc &msg)
{
	L_INFO("ReqLoginZone_sc");
	Player *player = PlayerMgr::Ins().CreatePlayer(msg.uin);
	L_COND_V(player);
	db::Player *playerData = db::TableCfg::Unpack<db::Player>(msg.playerData);
	L_COND_V(playerData);

	//do create player, enter
	Player *p;
	RspLoginZone_cs rsp;
	con.Send(rsp);
}

RegCenterMsg(LoginPlayer::ReqReLoginZone_sc);
void LoginPlayer::ReqReLoginZone_sc(ZoneSvrCon &con, const proto::ReqReLoginZone_sc &msg)
{
	L_INFO("ReqReLoginZone_sc");
	Player *player = PlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);

	L_COND_V(LoginOk == player->m_LoginPlayer.m_State || OffLine == player->m_LoginPlayer.m_State);
	const Session *sn = AccMgr::Ins().FindSessionByCid(msg.cid);
	WeakPlayer *weakPlayer = sn->GetEx<WeakPlayer>();
	L_COND_V(weakPlayer);
	*weakPlayer = player->GetWeakPtr();
	player->m_LoginPlayer.m_State = LoginOk;

	RspReLoginZone_cs rsp;
	rsp.ret = true;
	CenterCon::Ins().Send(rsp);
}
