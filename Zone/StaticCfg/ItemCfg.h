#pragma once
#include "dbStructDef.h"
#include "ItemDef.h"

struct ItemCfg
{
	uint32 weight = 100; //400 == 4.00 石
	ItemType type = ItemType::Base;
	string name = "a";
};


struct ItemCfgMgr 
{
	unordered_map<uint16, ItemCfg> m_ItemCfg;
	ItemCfgMgr();
};