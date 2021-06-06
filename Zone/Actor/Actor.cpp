#include "Actor.h"
#include "Player/PlayerMgr.h"

Actor::Actor(ActorOwner &owner, ActorType t)
	:EventCom<Actor>(m_owner)
	, m_owner(owner)
	, m_BaseAttr(*this)
	, m_ActorEquip(*this)
{
	Reg<EV_LOAD_DB>(&Actor::OnLoad);
}

void Actor::OnLoad(DbPlayer &data)
{

}

void Actor::EnterScene()
{

}

void Actor::PostDel()
{
	m_owner.PostDel();
}
