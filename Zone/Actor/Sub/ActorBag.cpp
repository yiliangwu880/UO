#include "Actor.h"

ActorBag::ActorBag(Actor &actor)
	:ActorSubCom<ActorBag>(actor.m_owner, actor)
{
	Reg<EV_LOAD_DB>(&ActorBag::OnLoad);
	Reg<EV_SAVE_DB>(&ActorBag::OnSave);
	Reg<EV_CREATE_DB>(&ActorBag::OnCreate);
}

void ActorBag::OnCreate(DbPlayer &data)
{
	SItem item= make_shared<Weapon>(0xF49);
	m_Container.Add(item);
}

void ActorBag::OnLoad(DbPlayer &data)
{
	m_Container.OnLoad(data.actor.bag);
}

void ActorBag::OnSave(DbPlayer &data)
{
	m_Container.OnSave(data.actor.bag);
}

