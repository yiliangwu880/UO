#include "Player.h"

Player::Player(uint64 uin, CStr &name)
	:ActorOwner(m_PlayerDb.GetDataWritable().actor) //整个Player 构造完整，才读写数据就没事
	,m_PlayerDb(*this)
	, m_BaseData(*this)
	, m_PlayerSn(*this)
	, m_SceneTran(*this)
	, m_LoginPlayer(*this)
	, m_Actor(*this, EntityType::Player)
{
	m_BaseData.m_uin = uin;
	m_BaseData.name = name;
}

void Player::SendHexStr(bool isFixed, const char *p)
{
	LogPacket t(isFixed);
	t.SetHexLog(p);
	Send(t);
}

