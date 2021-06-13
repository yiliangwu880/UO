//武器物品
#pragma once
#include "Item.h"


class Weapon : public Item
{
	//attr
	DbEquipItem m_dbEquipItem;
	const WeaponCfg *m_cfg = nullptr;
public:
	virtual void OnLoad(const DbItem &dbItem) override;
	virtual void OnSave(DbItem &dbItem) override;

public:
	Weapon(uint16 cfgId);
};


