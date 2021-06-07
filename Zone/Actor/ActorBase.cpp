#include "Actor.h"

ActorBase::ActorBase(Actor &owner)
	:EventCom<ActorBase>(owner.m_owner)
	,m_owner(owner)
{
	Reg<EV_SAVE_DB>(&ActorBase::OnSave);
}

void ActorBase::Init(const DbActorBase &base)
{
	m_base = base;
}

void ActorBase::OnSave(DbPlayer &data)
{
	DbActorBase &dbBase = data.actor.actorBase;
	dbBase.x = m_pos.X;
	dbBase.y = m_pos.Y;
	dbBase.z = m_pos.Z;
	dbBase.str = m_base.str;
	dbBase.dex = m_base.dex;
	dbBase.intl = m_base.intl;
}
