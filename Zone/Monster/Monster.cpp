#include "Monster.h"



void Monster::Init(const MonsterCfg &cfg, uint32 sceneId, const Point2D &pos)
{
	m_MonsterBase.Init(cfg);
}

Monster::Monster(uint32 uin)
	:m_actor(*this)
	, m_ai(*this, m_actor)
	, m_MonsterBase(*this)
{
	m_uin = uin;
}
