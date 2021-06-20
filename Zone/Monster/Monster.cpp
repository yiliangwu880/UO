#include "Monster.h"



Monster::Monster(uint32 uin)
	:ActorOwner(m_DbActor)
	,m_Actor(*this)
	, m_ai(*this, m_Actor)
	, m_MonsterBase(*this)
{
	m_uin = uin;
}


void Monster::Init(const MonsterInit &data)
{
	L_COND_V(data.cfg);
	L_COND_V(data.scene);

	//init m_DbActor ...

	FireEvent<EV_AFTER_INIT_DbActor>(m_DbActor);

	m_MonsterBase.Init(*data.cfg);
	m_Actor.EnterScene(*data.scene, (uint16)data.pos.X, (uint16)data.pos.Y);
}


