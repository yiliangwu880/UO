#pragma once
#include "Item.h"
#include "Container.h"
#include "Equip.h"
#include "ToolItem.h"
#include "Weapon.h"

using ItemCreator = shared_ptr<Item> (*)();

class ItemMgr : public Singleton<ItemMgr>
{
	map<uint32, ItemCreator> m_type2Creator;

public:
	static void Start(bool &ret);
	template<class T>
	inline static shared_ptr<Item> Creator()
	{
		return make_shared<T>();
	}

public:
	shared_ptr<Item> CreateItem(const DbItem &item);
	shared_ptr<Item> CreateItem(uint32 type);

};
