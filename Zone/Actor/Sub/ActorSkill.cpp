#include "Actor.h"

ActorSkill::ActorSkill(Actor &actor)
	:ActorSubCom<ActorSkill>(actor.m_owner, actor)
{
	Reg<EV_LOAD_DB>(&ActorSkill::OnLoad);
	Reg<EV_SAVE_DB>(&ActorSkill::OnSave);
}

void ActorSkill::OnLoad(DbActor &data)
{

}

void ActorSkill::OnSave(DbActor &data)
{

}
