#pragma once
#include "InsEvent.h"
#include "Scene/Aoi/Aoi.h"

class Actor;
class Observer : public EventCom<Observer> , public Aoi::Entity
{
	Actor &m_owner;

private:
	virtual void OnAddObserver(Entity &other); //other 看见我
	virtual void OnDelObserver(Entity &other); //other 看不见我

public:
	Observer(Actor &owner);
};