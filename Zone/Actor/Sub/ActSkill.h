//可执行的技能动作：比如普通攻击，特攻，治疗，魔法
#pragma once
#include "ActorSubCom.h"



class ActSkill : public ActorSubCom<ActSkill>
{
	map<uint32, uint32> m_id2lv;
public:
	ActSkill(Actor &actor);

private:
	void Act(uint32 id, const UnionTarget &target);

};