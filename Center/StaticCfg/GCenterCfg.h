//static cfg
#pragma once
#include "ItemCfg.h"
#include "MonsterCfg.h"

//game cfg
class GCfg : public Singleton<GCfg>
{
	//ItemCfgMgr m_ItemCfgMgr;
	//MonsterCfgMgr m_MonsterCfgMgr;

public:
	//const ItemCfg *GetItemCfg(uint16 id)const;
	//const WeaponCfg *GetWeaponCfg(uint16 id)const;
	//const DressCfg *GetDressCfg(uint16 id)const;
	//const MonsterCfg *GetMonsterCfg(uint32 id)const;
};
extern const GCfg &gCfg;

