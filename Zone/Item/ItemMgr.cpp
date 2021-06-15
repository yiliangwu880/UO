#include "ItemMgr.h"
#include "AppMgr.h"

GRegEvent(EV_SVR_START, ItemMgr::Start)
void ItemMgr::Start(bool &ret)
{
	ItemMgr::Ins().m_type2Creator[(uint32)ItemType::Base] = Creator<Item>;

#define ITEM_TYPE_NAME(t) ItemMgr::Ins().m_type2Creator[(uint32)ItemType::t] = Creator<t>;

	ALL_ITEM_TYPE_NAME

#undef ITEM_TYPE_NAME
}

std::shared_ptr<Item> ItemMgr::CreateItem(uint32 type, uint16 cfgId)
{
	auto it = m_type2Creator.find(type);
	if (it == m_type2Creator.end())
	{
		L_ERROR("create item  fail . type = %d", type);
		return nullptr;
	}
	ItemCreator f = it->second;
	return f(cfgId);
}

std::shared_ptr<Item> ItemMgr::CreateItem(const DbItem &item)
{
	uint16 cfgId = item.dbItemBase.cfgId;
	const ItemCfg *cfg = gCfg.GetItemCfg(cfgId);
	if (nullptr == cfg)
	{
		L_ERROR("find item cfg fail. id=%d", cfgId);
		return nullptr;
	}
	return ItemMgr::Ins().CreateItem((uint32)cfg->type, cfgId);
}
