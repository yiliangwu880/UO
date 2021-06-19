//zone static cfg
#pragma once
#include "ItemCfg.h"
#include "WeaponCfg.h"
#include "EquipCfg.h"

#include "MonsterCfg.h"
#include "SkillCfg.h"
#include "ActCfg.h"
#include "BuffCfg.h"

//game cfg
class GCfg : public Singleton<GCfg>
{
	friend class ActCfgMgr;

	ItemCfgMgr    m_ItemCfgMgr;
	WeaponCfgMgr    m_WeaponCfgMgr;
	EquipCfgMgr    m_EquipCfgMgr;
	MonsterCfgMgr m_MonsterCfgMgr;
	SkillCfgMgr   m_SkillCfgMgr;
	ActCfgMgr     m_ActCfgMgr;
	BuffCfgMgr       m_BuffCfgMgr;

public:
	const ItemCfg *GetItemCfg(uint16 id)const;
	const EquipCfg *GetEquipCfg(uint16 id)const;
	const WeaponCfg *GetWeaponCfg(uint16 id)const;
	const MonsterCfg *GetMonsterCfg(uint32 id)const;
	const SkillCfg *GetSkillCfg(uint32 id)const;
	const ActCfg *GetActCfg(uint32 id)const;
	const BuffCfg *GetBuffCfg(BuffId id)const;
};
extern const GCfg &gCfg;

