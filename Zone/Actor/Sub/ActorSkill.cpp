#include "Actor.h"

ActorSkill::ActorSkill(Actor &actor)
	:ActorSubCom<ActorSkill>(actor.m_owner, actor)
{
	Reg<EV_LOAD_DB>(&ActorSkill::OnLoad);
	Reg<EV_SAVE_DB>(&ActorSkill::OnSave);
}

void ActorSkill::OnLoad(DbPlayer &data)
{

}

void ActorSkill::OnSave(DbPlayer &data)
{

}
