#include "Actor.h"

ActorEquip::ActorEquip(Actor &actor)
	:ActorSubCom<ActorEquip>(actor.m_owner, actor)
{
	Reg<EV_CREATE_DB>(&ActorEquip::OnCreate);
	Reg<EV_LOAD_DB>(&ActorEquip::OnLoad);
	Reg<EV_SAVE_DB>(&ActorEquip::OnSave);
	Reg<EV_BEFORE_LOGIN>(&ActorEquip::OnBeforeLogin);
}

void ActorEquip::OnCreate(DbActor &dbActor)
{
	DbEquips &equips = dbActor.equips;
	if (m_Actor.m_ActorBase.GetType() == EntityType::Player)
	{
		{
			SItem item = make_shared<Equip>(0x1F7B);
			DbItem dbItem;
			item->OnSave(dbItem);
			equips.vecItem.push_back(dbItem);
		}
	}
}

void ActorEquip::OnLoad(DbActor &dbActor)
{
	DbEquips &equips = dbActor.equips;
	for (DbItem &v: equips.vecItem)
	{
		SItem p = ItemMgr::Ins().CreateItem(v);
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

void ActorEquip::OnSave(DbActor &dbActor)
{
	DbEquips &equips = dbActor.equips;
	equips.vecItem.clear();
	for (const SItem &item : m_items)
	{
		if (nullptr == item)
		{
			continue;
		}
		DbItem d;
		item->OnSave(d);
		equips.vecItem.push_back(d);
	}
}

void ActorEquip::OnBeforeLogin()
{
	m_items[(uint32)Layer::Backpack] = m_Actor.m_ActorBag.m_Container;
}

void ActorEquip::Undress(uint32 idx)
{
	L_COND_V(idx < m_items.size());
	L_COND_V(m_items[idx] != nullptr);
	m_Actor.m_ActorBag.m_Container->Add(m_items[idx]);
	m_items[idx] = nullptr;
}

void ActorEquip::Undress(SItem item)
{
	L_COND_V(item != nullptr);
	for (SItem &v : m_items)
	{
		if (item == v)
		{
			m_Actor.m_ActorBag.m_Container->Add(v);
			v = nullptr;
		}
	}
}

void ActorEquip::Dress(SItem item)
{
	Layer layer = item->GetLayer();
	uint32 idx = (uint32)layer;
	L_COND_V(idx < m_items.size());
	L_COND_V(m_items[idx] == nullptr);
	m_items[idx] = item;
	item->OnAdd(nullptr);
}

const ActorEquip::SItemArray & ActorEquip::GetItems() const
{
	return m_items;
}

SItem ActorEquip::GetItem(Layer layer)
{
	uint32 idx = (uint32)layer;
	L_COND(idx < m_items.size(), nullptr);
	return m_items[idx];
}
