#include "LoginPlayer.h"


void LoginPlayer::State(State state)
{

}


RegZoneMsg(ScenePlayer::RspLoginZone_cs);
void ScenePlayer::RspLoginZone_cs(ZoneSvrCon &con, const proto::RspLoginZone_cs &msg)
{
	L_INFO("ReqZoneOk_cs");
	Player *player = PlayerMgr::Ins().GetPlayer(msg.uin);
	L_COND_V(player);
	L_COND_V(Playing == player->m_SceneTran.m_State);


}
