//多才多艺的技能， 120 满
#pragma once
#include "ActorSubCom.h"


struct SkillInfo
{
	int skillID = 1; //cfgid
	string name = "Anatomy"; //skill name
};

class Skill
{
	const SkillCfg *m_SkillCfg = nullptr;
	DbSkill *m_DbSkill = nullptr;

public:

	void Init(DbSkill *dbSkill);
	int CapFixedPoint() { return m_DbSkill->cap; }//gm为1000点
	int BaseFixedPoint() { return m_DbSkill->base; }//gm为1000点
	SkillLock Lock();
	const DbSkill &GetDbSkill() { return *m_DbSkill; };
	const SkillCfg * GetCfg();
};

class ActorSkill : public ActorSubCom<ActorSkill>
{
	DbSkills *m_DbSkills = nullptr;
	std::array<Skill, (uint32)SkillName::Max> m_all;

public:
	ActorSkill(Actor &actor);
	uint32 Length() { return m_all.size(); }
	Skill *GetSkill(uint32 idx);

private:
	void OnCreate(DbActor &data);
	void OnLoad(DbActor &data);

};