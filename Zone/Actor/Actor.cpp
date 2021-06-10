#include "Actor.h"
#include "Player/PlayerMgr.h"

Actor::Actor(ActorOwner &owner, EntityType t)
	:EventCom<Actor>(owner)
	, m_owner(owner)
	, m_ActorBase(*this)
	, m_ActorEquip(*this)
	, m_Observer(*this, t)
	, m_StateMgr(*this)
	, m_BuffMgr(*this)
{
}

void Actor::InitMonster(const MonsterInit &data)
{
	m_ActorBase.InitMonster(data);
}

void Actor::EnterScene(uint32 id)
{
	Scene *p = SceneMgr::Ins().Find(id);
	L_COND_V(p);
	
	auto &pos = m_ActorBase.GetPos();
	m_Observer.Enter(p->m_aoi, pos.X, pos.Y);
}

bool Actor::EnterScene(Scene &scene, uint16 x, uint16 y)
{
	m_ActorBase.SetPos(Point3D(x, y, 0));
	return m_Observer.Enter(scene.m_aoi, x, y);
}


