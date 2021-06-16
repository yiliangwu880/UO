//武器物品
#pragma once
#include "Item.h"

class Actor;
struct IWeapon
{
	//int MaxRange{ get; }
	//void OnBeforeSwing(Mobile attacker, IDamageable damageable);
	//TimeSpan OnSwing(Mobile attacker, IDamageable damageable);
	virtual void GetStatusDamage(Actor &from, int &min, int &max);
	//TimeSpan GetDelay(Mobile attacker);
};

class Weapon : public Item, public IWeapon
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


class Fists : public IWeapon
{

};