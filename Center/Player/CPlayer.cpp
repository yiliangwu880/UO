#include "CPlayer.h"


CPlayer::CPlayer()
	:m_BaseData(*this)
	, m_SceneTran(*this)
	, m_LoginPlayer(*this)
{

}

void CPlayer::SetSid(const acc::SessionId &sid)
{
	m_sid = sid;
}


