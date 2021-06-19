//装备，衣服等可穿戴物品
#pragma once
#include "Item.h"


class Equip : public Item
{
	friend class ItemMgr;

	//attr
	DbEquipItem m_dbEquipItem;
	const EquipCfg *m_cfg = nullptr;

public:
	virtual void OnLoad(const DbItem &dbItem) override;
	virtual void OnSave(DbItem &dbItem) override;
	virtual Layer GetLayer()const override;

private:
	Equip(uint16 cfgId);
};


