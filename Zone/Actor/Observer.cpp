#include "Actor.h"

void Observer::OnAddObserver(Entity &other)
{

}

void Observer::OnDelObserver(Entity &other)
{

}

Observer::Observer(Actor &actor, EntityType type)
	:ActorSubCom<Observer>(actor.m_owner, actor)
	, Aoi::Entity(type)
{

}