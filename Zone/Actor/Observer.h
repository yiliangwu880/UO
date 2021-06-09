#pragma once
#include "ActorSubCom.h"
#include "Scene/Aoi/Aoi.h"

class Actor;
class Observer : public ActorSubCom<Observer>, public Aoi::Entity
{
private:
	virtual void OnAddObserver(Entity &other); //other 看见我
	virtual void OnDelObserver(Entity &other); //other 看不见我

public:
	Observer(Actor &actor, EntityType t);
};