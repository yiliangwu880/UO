#include "Player.h"

Player::Player(uint64 uin, CStr &name)
	:m_BaseData(*this)
	, m_PlayerDb(*this)
	, m_PlayerSn(*this)
	, m_SceneTran(*this)
	, m_LoginPlayer(*this)
	, m_ActorMgr(*this)
	, m_Actor(*this)
{
	m_BaseData.m_uin = uin;
	m_BaseData.name = name;
}

