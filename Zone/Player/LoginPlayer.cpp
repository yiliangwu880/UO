#include "PlayerMgr.h"

using namespace proto;
using namespace acc;

void LoginPlayer::ClientDisCon()
{
	L_COND_V(LoginOk == m_State);
	m_State = OffLine;
}

RegCenterMsg(LoginPlayer::ReqLoginZone_sc);
void LoginPlayer::ReqLoginZone_sc(CenterCon &con, const proto::ReqLoginZone_sc &msg)
{
	L_INFO("ReqLoginZone_sc");
	std::unique_ptr<BaseTable> baseTable = TableCfg::Ins().Unpack(msg.playerData);
	DbPlayer * playerData = dynamic_cast<DbPlayer *>(baseTable.get());
	L_COND_V(playerData);

	Player *player = PlayerMgr::Ins().CreatePlayer(playerData->uin, playerData->name);
	L_COND_V(player);

	//do create player, enter
	Player *p;
	RspLoginZone_cs rsp;
	con.Send(rsp);
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
	*weakPlayer = player->GetWeakPtr();
	player->m_LoginPlayer.m_State = LoginOk;

	RspReLoginZone_cs rsp;
	rsp.ret = true;
	CenterCon::Ins().Send(rsp);
}
