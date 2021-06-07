#include "GCfg.h"

const GCfg &gCfg = GCfg::Ins();

const ItemCfg * GCfg::GetItemCfg(uint16 id)
{
	return MapFind(ItemCfgMgr::Ins().m_ItemCfg, id);
}

const WeaponCfg * GCfg::GetWeaponCfg(uint16 id)
{
	return MapFind(ItemCfgMgr::Ins().m_WeaponCfg, id);
}

const DressCfg * GCfg::GetDressCfg(uint16 id)
{
	return MapFind(ItemCfgMgr::Ins().m_DressCfg, id);
}

const MonsterCfg * GCfg::GetMonsterCfg(uint32 id)
{
	return MapFind(MonsterCfgMgr::Ins().m_MonsterCfg, id);
}
