#include "PlayerMgr.h"

using namespace proto;
using namespace acc;

void LoginPlayer::Login()
{
	m_owner.m_Actor.EnterScene();
	m_owner.FireEvent<EV_BEFORE_LOGIN>(); 
	SendLogin();
}

void LoginPlayer::SendLogin()
{

}

void LoginPlayer::ClientDisCon()
{
	L_COND_V(LoginOk == m_State);
	m_State = OffLine;
}

RegCenterMsg(LoginPlayer::ReqLoginZone_sc);
void LoginPlayer::ReqLoginZone_sc(CenterCon &con, const proto::ReqLoginZone_sc &msg)
{
	std::unique_ptr<BaseTable> baseTable = TableCfg::Ins().Unpack(msg.playerData);
	DbPlayer * playerData = dynamic_cast<DbPlayer *>(baseTable.get());
	L_COND_V(playerData);
	L_INFO("player %s login zone.", playerData->name.c_str());

	Player *player = PlayerMgr::Ins().CreatePlayer(playerData->uin, playerData->name);
	L_COND_V(player);

	acc::SessionId sid;
	sid.cid = msg.cid;
	player->m_PlayerSn.SetSid(sid);

	RspLoginZone_cs rsp;
	rsp.uin = playerData->uin;
	rsp.ret = true;
	con.Send(rsp);

	player->m_PlayerDb.OnLoad(*playerData);
	player->m_LoginPlayer.Login();
}

RegCenterMsg(LoginPlayer::ReqReLoginZone_sc);
void LoginPlayer::ReqReLoginZone_sc(CenterCon &con, const proto::ReqReLoginZone_sc &msg)
{
	L_INFO("ReqReLoginZone_sc");
	Player *player = PlayerMgr::Ins().FindPlayer(msg.uin);
	L_COND_V(player);

	L_COND_V(LoginOk == player->m_LoginPlayer.m_State || OffLine == player->m_LoginPlayer.m_State);
	const Session *sn = AccMgr::Ins().FindSessionByCid(msg.cid);
	WeakPlayer *weakPlayer = sn->GetEx<WeakPlayer>();
	L_COND_V(weakPlayer);
	*weakPlayer = *player;
	player->m_LoginPlayer.m_State = LoginOk;

	RspReLoginZone_cs rsp;
	rsp.ret = true;
	CenterCon::Ins().Send(rsp);
}
