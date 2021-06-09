#include "Monster.h"





void Monster::Init(const MonsterInit &data)
{
	L_COND_V(data.cfg);
	L_COND_V(data.scene);
	m_MonsterBase.Init(*data.cfg);
	Enter(*data.scene, (uint16)data.pos.X, (uint16)data.pos.Y);
}

Monster::Monster(uint32 uin)
	:m_actor(*this)
	, m_ai(*this, m_actor)
	, m_MonsterBase(*this)
{
	m_uin = uin;
}

bool Monster::Enter(Scene &scene, uint16 x, uint16 y)
{
	return m_actor.m_Observer.Enter(scene.m_aoi, x, y);
}
