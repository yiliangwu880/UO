#include "Actor.h"

ActorBase::ActorBase(Actor &actor)
	:ActorSubCom<ActorBase>(actor.m_owner, actor)
{
	Reg<EV_LOAD_DB>(&ActorBase::OnLoad);
	Reg<EV_SAVE_DB>(&ActorBase::OnSave);

}
void ActorBase::OnLoad(DbPlayer &data)
{
	const DbActorBase &dbBase = data.actor.actorBase;
	m_str     = dbBase.str;
	m_dex     = dbBase.dex;
	m_intl    = dbBase.intl;
	m_pos.X   = dbBase.x;
	m_pos.Y   = dbBase.y;
	m_pos.Z   = dbBase.z;
	m_female  = m_female;
	m_race    = m_race;
}

void ActorBase::InitMonster(const MonsterInit &data)
{
	m_str = data.cfg->str;
	m_dex = data.cfg->dex;
	m_intl = data.cfg->intl;
	m_hp = m_str;
}

void ActorBase::OnSave(DbPlayer &data)
{
	DbActorBase &dbBase = data.actor.actorBase;
	dbBase.str  = m_str;
	dbBase.dex  = m_dex;
	dbBase.intl = m_intl;
	dbBase.x = m_pos.X;
	dbBase.y = m_pos.Y;
	dbBase.z = m_pos.Z;
}

