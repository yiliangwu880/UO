#include "ItemMgr.h"
#include "SceneMgr.h"

Item::Item()
	:m_observer(*this)
{
	static uint32 seedId = 0;
	seedId++;
	m_id = seedId;
}

void Item::OnLoad(const DbItem &dbItem)
{
	const ItemCfg *p = gCfg.GetItemCfg(dbItem.dbItemBase.cfgId);
	if (nullptr == p)
	{
		p = gCfg.GetItemCfg(0);
	}
	m_cfg = p;
}

void Item::OnSave(DbItem &dbItem)
{

}

void Item::SetPos(uint16 x, uint16 y, uint16 z /*= 0*/)
{
	m_pos = Point3D(x, y, z);
}

ItemObserver::ItemObserver(Item &item)
	:Aoi::Entity(EntityType::Item)
	, m_Item(item)
{

}
void ItemObserver::OnAddObserver(Entity &other)
{

}

void ItemObserver::OnDelObserver(Entity &other)
{

}


bool ItemObserver::Enter(Scene &scene, uint16_t x, uint16_t y)
{
	bool r = Aoi::Entity::Enter(scene.m_aoi, x, y);
	if (r)
	{
		m_Item.SetPos(x, y);
	}
	return r;
}

bool ItemObserver::Leave()
{
	return Aoi::Entity::Leave();
}
