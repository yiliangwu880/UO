#include "Actor.h"

ActorEquip::ActorEquip(Actor &actor)
	:ActorSubCom<ActorEquip>(actor.m_owner, actor)
{
	Reg<EV_CREATE_DB>(&ActorEquip::OnCreate);
	Reg<EV_LOAD_DB>(&ActorEquip::OnLoad);
	Reg<EV_SAVE_DB>(&ActorEquip::OnSave);
}

void ActorEquip::OnCreate(DbPlayer &dbActor)
{
}

void ActorEquip::OnLoad(DbPlayer &dbActor)
{
	DbEquips &equips = dbActor.actor.equips;
	for (DbItem &v: equips.vecItem)
	{
		shared_ptr<Item> p = ItemMgr::Ins().CreateItem(v);
		if (nullptr == p)
		{
			L_ERROR("create item  fail");
			continue;
		}
		Layer layer = p->GetLayer();
		uint32 idx = (uint32)layer;
		if (idx >= m_items.size())
		{
			L_ERROR("layer overflow %d", idx);
			continue;
		}
		if (m_items[idx] != nullptr)
		{
			L_ERROR("add item in same layer");
			continue;
		}
		m_items[idx] = p;
	}
}

void ActorEquip::OnSave(DbPlayer &dbActor)
{
	DbEquips &equips = dbActor.actor.equips;
	for (const shared_ptr<Item> &item : m_items)
	{
		DbItem d;
		item->OnSave(d);
		equips.vecItem.push_back(d);
	}
}