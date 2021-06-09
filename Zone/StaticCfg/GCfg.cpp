#include "GCfg.h"

const GCfg &gCfg = GCfg::Ins();



const ItemCfg * GCfg::GetItemCfg(uint16 id)const
{
	return MapFind(m_ItemCfgMgr.m_ItemCfg, id);
}

const WeaponCfg * GCfg::GetWeaponCfg(uint16 id)const
{
	return MapFind(m_ItemCfgMgr.m_WeaponCfg, id);
}

const DressCfg * GCfg::GetDressCfg(uint16 id)const
{
	return MapFind(m_ItemCfgMgr.m_DressCfg, id);
}

const MonsterCfg * GCfg::GetMonsterCfg(uint32 id)const
{
	return MapFind(m_MonsterCfgMgr.m_MonsterCfg, id);
}
