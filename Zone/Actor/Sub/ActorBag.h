#pragma once
#include "ActorSubCom.h"
#include "Item/ItemMgr.h"

class ActorBag : public ActorSubCom<ActorBag>
{
public:
	shared_ptr<Container> m_Container;

public:
	ActorBag(Actor &actor);
	

private:
	void OnCreate(DbActor &data);
	void OnLoad(DbActor &data);
	void OnSave(DbActor &data);

};