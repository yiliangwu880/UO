//全局游戏配置，正式很少改动的，放代码更方便
//其他代码都通过  GCfg访问，才能保证不会运行代码不会修改配置内存
#pragma once
#include "MiscCfg.h"
#include "ItemCfg.h"
#include "MonsterCfg.h"

//game cfg
class GCfg : public Singleton<GCfg>
{
	MiscCfg m_MiscCfg;
	ItemCfgMgr m_ItemCfgMgr;
	MonsterCfgMgr m_MonsterCfgMgr;

public:
	const MiscCfg &GetMiscCfg()const { return m_MiscCfg; }
	const ItemCfg *GetItemCfg(uint16 id)const;
	const WeaponCfg *GetWeaponCfg(uint16 id)const;
	const DressCfg *GetDressCfg(uint16 id)const;
	const MonsterCfg *GetMonsterCfg(uint32 id)const;
};
extern const GCfg &gCfg;

