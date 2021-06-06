#include "Actor.h"
#include "Player/PlayerMgr.h"

Actor::Actor(ActorOwner &owner, ActorType t)
	:m_owner(owner)
	, m_BaseAttr(*this)
	, m_ActorEquip(*this)
{

}

void Actor::Init(const DbActor &dbActor)
{

}

void Actor::PostDel()
{
	m_owner.PostDel();
}
