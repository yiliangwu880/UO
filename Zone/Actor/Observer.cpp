#include "Actor.h"

void Observer::OnAddObserver(Entity &other)
{

}

void Observer::OnDelObserver(Entity &other)
{

}

Observer::Observer(Actor &owner, EntityType type)
	:EventCom<Observer>(owner.m_owner)
	, Aoi::Entity(type)
	, m_owner(owner)
{

}