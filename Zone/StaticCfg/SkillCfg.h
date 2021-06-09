#pragma once
#include "Act.h"


struct SkillCfg
{
	uint16 id;
	uint32 actId;
};

struct SkillCfgMgr 
{
	unordered_map<uint16, SkillCfg> m_SkillCfg;

	SkillCfgMgr();
};