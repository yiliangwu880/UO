#include "PlayerMgr.h"

Player * PlayerMgr::CreatePlayer(uint64 uin)
{
	return nullptr;
}
Player * PlayerMgr::GetPlayer(uint64 uin)
{
	return nullptr;
}

STATIC_RUN(MsgDispatch<CenterCon>::Ins().RegMsgHandler(&PlayerMgr::ReqLoginZone_sc));
static void PlayerMgr::ReqLoginZone_sc(CenterCon &con, const proto::ReqLoginZone_sc &msg)
{
	L_INFO("ReqLoginZone_sc");
	db::Player *playerData = db::TableCfg::Unpack<db::Player>(msg.playerData);
	L_COND_V(playerData);

	//do create player, enter
	Player *p;
	RspLoginZone_cs rsp;
	con.Send(rsp);

}