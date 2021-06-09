#include "Actor.h"

ActorEquip::ActorEquip(Actor &actor)
	:ActorSubCom<ActorEquip>(actor.m_owner, actor)
{
	Reg<EV_LOAD_DB>(&ActorEquip::OnLoad);
}

void ActorEquip::OnLoad(DbPlayer &dbActor)
{
	m_equips = &dbActor.actor.equips;
}
