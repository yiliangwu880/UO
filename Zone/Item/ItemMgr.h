#pragma once
#include "Item.h"
#include "Container.h"
#include "Equip.h"
#include "ItemTool.h"
#include "Weapon.h"

using ItemCreator = shared_ptr<Item> (*)(uint16 cfgId);


class ItemMgr : public Singleton<ItemMgr>
{
	map<uint32, ItemCreator> m_type2Creator;
	unordered_map<uint32, SItem> m_id2Item;

public:
	static void Start(bool &ret);

private:
	template<class T>
	inline static shared_ptr<Item> Creator(uint16 cfgId)
	{
		return shared_ptr<T>(new T(cfgId));
	}

public:
	SItem Find(uint32 id);
	shared_ptr<Item> CreateItem(const DbItem &item);
	//item唯一创建入口
	shared_ptr<Item> CreateItem(ItemType type, uint16 cfgId);
	//同 CreateItem
	template<class T>
	shared_ptr<T> CreateItemByType(uint16 cfgId)
	{
		shared_ptr<T> item(new T(cfgId));
		bool r = MapInsert(m_id2Item, item->Serial(), item);
		L_COND(r, nullptr, "create new item fail, id=%d, type=%d", item->Serial(),  (uint32)(item->GetType()));
		return item;
	}

};
