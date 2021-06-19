#include "Actor.h"
#include "ItemMgr.h"

ActorBag::ActorBag(Actor &actor)
	:ActorSubCom<ActorBag>(actor.m_owner, actor)
	, m_Container(ItemMgr::Ins().CreateItemByType<Container>(0xE75))
{
	

	Reg<EV_LOAD_DB>(&ActorBag::OnLoad);
	Reg<EV_SAVE_DB>(&ActorBag::OnSave);
	Reg<EV_CREATE_DB>(&ActorBag::OnCreate);
}

void ActorBag::OnCreate(DbActor &data)
{
	{
		SItem item = ItemMgr::Ins().CreateItem(ItemType::Weapon, 0xF49);
		m_Container->Add(item);
	}
	if (m_Actor.m_ActorBase.GetType() == EntityType::Player)
	{
		{
			SItem item = ItemMgr::Ins().CreateItem(ItemType::Equip, 0x1517); 
			m_Container->Add(item);
		}
	}
	//init db
	m_Container->OnSave(data.bag);

}

void ActorBag::OnLoad(DbActor &data)
{
	m_Container->OnLoad(data.bag);
}

void ActorBag::OnSave(DbActor &data)
{
	m_Container->OnSave(data.bag);
}


