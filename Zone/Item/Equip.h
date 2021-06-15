//装备，衣服等可穿戴物品
#pragma once
#include "Item.h"


class Equip : public Item
{
	//attr
	DbEquipItem m_dbEquipItem;
	const EquipCfg *m_cfg = nullptr;

public:
	virtual void OnLoad(const DbItem &dbItem) override;
	virtual void OnSave(DbItem &dbItem) override;

public:
	Equip(uint16 cfgId);
};


