#pragma once
#include "Act.h"


struct SkillCfg
{
	uint32 skillID;
	string name;
	double strScale;
	double dexScale;
	double intScale;
	string title;
	void *callback;//SkillUseCallback callback;
	double strGain;
	double dexGain;
	double intGain;
	double gainFactor;
	StatType primary;
	StatType secondary;
	bool mastery = false;
	bool usewhilecasting = false;
};

struct SkillCfgMgr 
{
	unordered_map<uint32, SkillCfg> m_SkillCfg;

	SkillCfgMgr();
};