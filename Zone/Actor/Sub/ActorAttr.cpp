#include "Actor.h"

ActorAttr::ActorAttr(Actor &actor)
	:ActorSubCom<ActorAttr>(actor.m_owner, actor)
{
	Reg<EV_LOAD_DB>(&ActorAttr::OnLoad);
	Reg<EV_SAVE_DB>(&ActorAttr::OnSave);
	Reg<EV_CREATE_DB>(&ActorAttr::OnCreate);

}

void ActorAttr::OnCreate(DbPlayer &data)
{
	DbActorAttr &d = data.actor.actorAttr;
	d.hits = 50;
	d.stam = 50;
	d.mana = 50;
}

void ActorAttr::OnLoad(DbPlayer &data)
{
	const DbActorAttr &d = data.actor.actorAttr;
	m_data     = d;
}

void ActorAttr::OnSave(DbPlayer &data)
{
	data.actor.actorAttr = m_data;
}


void ActorAttr::InitMonster(const MonsterInit &data)
{
	m_data.str = data.cfg->str;
	m_data.dex = data.cfg->dex;
	m_data.intl = data.cfg->intl;
	m_data.hits = m_data.str;
}

uint32 ActorAttr::Hits()
{
	return m_data.hits;
}

uint32 ActorAttr::HitsMax()
{
	return 50 + (m_data.str / 2);
}

uint16 ActorAttr::Mana()
{
	return 50;
}

uint16 ActorAttr::Stam()
{
	return 50;
}

uint16 ActorAttr::ManaMax()
{
	return 50;
}

uint16 ActorAttr::StamMax()
{
	return 50;
}
