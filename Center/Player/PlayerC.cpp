#include "PlayerC.h"


PlayerC::PlayerC(const DbPlayer &data)
	:m_BaseData(*this)
	, m_CPlayerSn(*this)
	, m_SceneTran(*this)
	, m_LoginPlayer(*this)
{
	L_DEBUG("PlayerC create. uin,name=%ld, %s", data.uin, data.name.c_str());
	m_BaseData.m_uin = data.uin;
	m_BaseData.name = data.name;
}



