#include "Player.h"


void Player::SetSid(const acc::SessionId &sid)
{
	m_sid = sid;
}

void Player::LoginZone()
{
	uint16 svrId = 1; //find by data db.
//req zone enter player
	ZoneSvr *svr = ZoneSvrMgr::Ins().FindZoneSvr(svrId);
	L_COND_V(svr);
	proto::ReqLoginZone_sc msg;
	TableCfg::Ins().Pack(data, msg.playerData);
	svr->Send(msg);
}

