#include "Actor.h"

ActorBag::ActorBag(Actor &actor)
	:ActorSubCom<ActorBag>(actor.m_owner, actor)
{
	Reg<EV_LOAD_DB>(&ActorBag::OnLoad);
	Reg<EV_SAVE_DB>(&ActorBag::OnSave);
	Reg<EV_CREATE_DB>(&ActorBag::OnCreate);
	Reg<EV_CREATE_PLAYER_DB>(&ActorBag::OnCreatePlayer);
}

void ActorBag::OnCreate(DbActor &data)
{
}

void ActorBag::OnLoad(DbActor &data)
{
	m_Container.OnLoad(data.bag);
}

void ActorBag::OnSave(DbActor &data)
{
	m_Container.OnSave(data.bag);
}

void ActorBag::OnCreatePlayer(DbPlayer &data)
{
	{
		SItem item = make_shared<Weapon>(0xF49);
		m_Container.Add(item);
	}
	SItem item = make_shared<Equip>(1);
}

