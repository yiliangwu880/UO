#include "Actor.h"
#include "Player/PlayerMgr.h"
#include "SceneMgr.h"

Actor::Actor(ActorOwner &owner, EntityType t)
	:EventCom<Actor>(m_owner)
	, m_owner(owner)
	, m_ActorBase(*this)
	, m_ActorEquip(*this)
	, m_Observer(*this, t)
{
	Reg<EV_LOAD_DB>(&Actor::OnLoad);
}

void Actor::OnLoad(DbPlayer &data)
{
	m_ActorBase.Init(data.actor.actorBase);
}

void Actor::EnterScene(uint32 id)
{
	Scene *p = SceneMgr::Ins().FindScene(id);
	L_COND_V(p);
	
	auto &pos = m_ActorBase.GetPos();
	m_Observer.Enter(p->m_aoi, pos.X, pos.Y);
}

void Actor::PostDel()
{
	m_Observer.Leave(); //先离开场景，不能留着析构过程离开，不然导致析构调用虚函数就出问题了。
	m_owner.PostDel();
}
