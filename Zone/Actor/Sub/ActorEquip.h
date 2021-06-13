#pragma once
#include "ActorSubCom.h"
#include "Item/ItemMgr.h"

class ActorEquip : public ActorSubCom<ActorEquip>
{
	std::array<shared_ptr<Item>, (uint32)Layer::Max> m_items;

public:
	ActorEquip(Actor &actor);
	void OnCreate(DbPlayer &dbActor);
	void OnLoad(DbPlayer &dbActor);
	void OnSave(DbPlayer &dbActor);
};