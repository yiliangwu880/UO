#include "Actor.h"

ActorEquip::ActorEquip(Actor &owner)
	:EventCom<ActorEquip>(owner.m_owner)
	,m_owner(owner)
{
	Reg<EV_LOAD_DB>(&ActorEquip::OnLoad);
}

void ActorEquip::OnLoad(DbPlayer &dbActor)
{
	m_equips = &dbActor.actor.equips;
}
