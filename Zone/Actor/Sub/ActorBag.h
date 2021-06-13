#pragma once
#include "ActorSubCom.h"
#include "Item/ItemMgr.h"

class ActorBag : public ActorSubCom<ActorBag>
{
	Container m_Container;

public:
	ActorBag(Actor &actor);

private:
	void OnCreate(DbPlayer &data);
	void OnLoad(DbPlayer &data);
	void OnSave(DbPlayer &data);

};