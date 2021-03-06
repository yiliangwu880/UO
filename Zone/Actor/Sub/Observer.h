#pragma once
#include "ActorSubCom.h"
#include "Scene/Aoi/Aoi.h"

class Actor;
class Observer : public ActorSubCom<Observer>, public Aoi::Entity
{
private:
	virtual void OnAddObserver(Entity &other); //other 看见我
	virtual void OnDelObserver(Entity &other); //other 看不见我
	virtual void OnActivate(); //被玩家激活。 （有任意玩家在附近）
	virtual void OnDeactivate();

public:
	Observer(Actor &actor, EntityType t);
	bool Enter(Scene &scene, uint16_t x, uint16_t y);
	bool Leave();
};