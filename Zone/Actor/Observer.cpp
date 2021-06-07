#include "Actor.h"

void Observer::OnAddObserver(Entity &other)
{

}

void Observer::OnDelObserver(Entity &other)
{

}

Observer::Observer(Actor &owner)
	:EventCom<Observer>(owner.m_owner)
	, m_owner(owner)
{

}