//zone static cfg
#pragma once
#include "ItemCfg.h"
#include "MonsterCfg.h"
#include "SkillCfg.h"
#include "ActCfg.h"
#include "BuffCfg.h"

//game cfg
class GCfg : public Singleton<GCfg>
{
	friend class ActCfgMgr;

	ItemCfgMgr    m_ItemCfgMgr;
	MonsterCfgMgr m_MonsterCfgMgr;
	SkillCfgMgr   m_SkillCfgMgr;
	ActCfgMgr     m_ActCfgMgr;
	BuffCfgMgr       m_BuffCfgMgr;

public:
	const ItemCfg *GetItemCfg(uint16 id)const;
	const WeaponCfg *GetWeaponCfg(uint16 id)const;
	const DressCfg *GetDressCfg(uint16 id)const;
	const MonsterCfg *GetMonsterCfg(uint32 id)const;
	const SkillCfg *GetSkillCfgMgr(uint32 id)const;
	const ActCfg *GetActCfgMgr(uint32 id)const;
	const BuffCfg *GetBuffCfgMgr(BuffId id)const;
};
extern const GCfg &gCfg;

