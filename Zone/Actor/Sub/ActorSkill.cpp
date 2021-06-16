#include "Actor.h"

ActorSkill::ActorSkill(Actor &actor)
	:ActorSubCom<ActorSkill>(actor.m_owner, actor)
{
	Reg<EV_CREATE_DB>(&ActorSkill::OnCreate);
	Reg<EV_LOAD_DB>(&ActorSkill::OnLoad);
	Reg<EV_SAVE_DB>(&ActorSkill::OnSave);
}

Skill * ActorSkill::GetSkill(uint32 idx)
{
	return &m_all[SkillName::Anatomy];
}

void ActorSkill::OnCreate(DbActor &data)
{
	{//tmp skill
		m_all[SkillName::Anatomy] = Skill();
	}
	
}
void ActorSkill::OnLoad(DbActor &data)
{

}

void ActorSkill::OnSave(DbActor &data)
{

}
