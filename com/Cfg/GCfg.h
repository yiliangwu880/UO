//全局游戏配置，正式很少改动的，放代码更方便
#pragma once
#include "ItemCfg.h"
#include "MonsterCfg.h"

//game cfg
class GCfg : public Singleton<GCfg>
{
	
public:
	const ItemCfg *GetItemCfg(uint16 id);
	const WeaponCfg *GetWeaponCfg(uint16 id);
	const DressCfg *GetDressCfg(uint16 id);
	const MonsterCfg *GetMonsterCfg(uint32 id);
};
extern const GCfg &gCfg;

