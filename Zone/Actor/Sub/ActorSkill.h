//多才多艺的技能， 120 满
#pragma once
#include "ActorSubCom.h"


struct SkillInfo
{
	int skillID = 1; //cfgid
	string name = "Anatomy"; //skill name
};
struct Skill
{
	uint16 base=0; //0~1200
	int lockState=0;//unlock, up , down
	SkillInfo Info;
	SkillLock m_Lock = SkillLock::Up;
	int CapFixedPoint() { return 1000; }
	int BaseFixedPoint() { return 500; }
	SkillLock Lock() { return m_Lock; }
};
class ActorSkill : public ActorSubCom<ActorSkill>
{
	map<SkillName, Skill> m_all;
public:
	ActorSkill(Actor &actor);
	uint32 Length() { return m_all.size(); }
	Skill *GetSkill(uint32 idx);

private:
	void OnCreate(DbActor &data);
	void OnLoad(DbActor &data);
	void OnSave(DbActor &data);

};