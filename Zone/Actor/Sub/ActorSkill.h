//多才多艺的技能， 120 满
#pragma once
#include "ActorSubCom.h"


struct Skill
{
	uint16 base; //0~1200
	int lockState;//unlock, up , down
};
class ActorSkill : public ActorSubCom<ActorSkill>
{
	map<SkillName, Skill> m_all;
public:
	ActorSkill(Actor &actor);

private:
	void OnLoad(DbPlayer &data);
	void OnSave(DbPlayer &data);

};