/*
技能可以产生动作。技能有等级属性，等级高产生动作效果更高
*/
#pragma once

#include <vector>
#include <map>
#include <functional>
#include "com.h"
#include "cfg.h"

class SkillMgr
{
	Actor m_owner;
	std::map<int, Skill> m_id2Skill;
public:
	//地震,哈斯卡debuff,普通攻击技能 ， 。。。
	void UseSkill(Skill &skill, Actor *target = nullptr)
	{
		SkillCfg cfg = skill.GetSkillCfg();
		for (ActionEffect ae : cfg.vecAe)
		{
			auto anys = ae.chgFun(ae.anys, skill.lv, *this, target);
			(*ae.action)(ae.anys, m_owner, target);
		}
	}

}
class Skill
{
public:
	static const int ID = 1;
	int id, lv;

	const SkillCfg &GetSkillCfg()
	{
		return allSkillCfg[ID];
	}

private:
};
