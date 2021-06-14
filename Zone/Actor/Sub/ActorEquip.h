#pragma once
#include "ActorSubCom.h"
#include "Item/ItemMgr.h"

class ActorEquip : public ActorSubCom<ActorEquip>
{
	std::array<SItem, (uint32)Layer::Max> m_items;

public:
	ActorEquip(Actor &actor);
	void OnCreate(DbActor &dbActor);
	void OnLoad(DbActor &dbActor);
	void OnSave(DbActor &dbActor);
	void Undress(uint32 idx);
	void Undress(SItem item);
	void Dress(SItem item);
};