#include "Monster.h"

void Monster::PostDel()
{
	delete this;
}

Monster::Monster(uint32 uin)
	:m_actor(*this)
	, m_ai(*this, m_actor)
	, m_MonsterBase(*this)
{
	m_uin = uin;
}
