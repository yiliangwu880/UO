#include "ItemMgr.h"
#include "SceneMgr.h"
#include "ZoneMisc.h"

Item::Item(uint16 cfgId)
	:m_observer(*this)
{
	m_id = Serial::NewItem();
	m_cfgId = cfgId;
	const ItemCfg *p = gCfg.GetItemCfg(cfgId);
	if (nullptr == p)
	{
		L_ERROR("find item cfg error. id=%d", cfgId);
		p = gCfg.GetItemCfg(0xE21);
		m_cfgId = 0xE21;
	}
	m_cfg = p;
}

Item::~Item()
{

}

void Item::OnLoad(const DbItem &dbItem)
{
	m_pos = Point3D(dbItem.dbItemBase.x, dbItem.dbItemBase.y, 0);
	m_num = dbItem.dbItemBase.num;
}

void Item::OnSave(DbItem &dbItem)
{
	dbItem.dbItemBase.cfgId = m_cfgId;
	dbItem.dbItemBase.num = m_num;
	dbItem.dbItemBase.x = m_pos.X;
	dbItem.dbItemBase.y = m_pos.Y;
}

void Item::OnAdd(Container *parent)
{
	if (auto p = m_parent.lock())
	{
		p->Remove(this);
	}

	m_parent.reset();
	if (nullptr != parent)
	{
		m_parent = parent->shared_from_this();
	}
}

void Item::SetPos(uint16 x, uint16 y, uint16 z /*= 0*/)
{
	m_pos = Point3D(x, y, z);
}

ItemType Item::GetType() const
{
	return m_cfg->type;
}

Container *Item::GetParent()
{
	auto p = m_parent.lock();
	if (nullptr == p)
	{
		return nullptr;
	}
	return p.get();
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

	m_Item.OnAdd(nullptr);
	return r;
}

bool ItemObserver::Leave()
{
	return Aoi::Entity::Leave();
}
