#pragma once
#include "ActorSubCom.h"
#include "Item/ItemMgr.h"

using EquipSItems = std::array<SItem, (uint32)Layer::Max>;
class ActorEquip : public ActorSubCom<ActorEquip>
{
	EquipSItems m_items;

public:
	ActorEquip(Actor &actor);
	void OnCreate(DbActor &dbActor);
	void OnLoad(DbActor &dbActor);
	void OnSave(DbActor &dbActor);
	void OnBeforeLogin();
	void Undress(uint32 idx);
	void Undress(SItem item);
	void Dress(SItem item);
	EquipSItems &GetItems();
	SItem GetItem(Layer layer);
};