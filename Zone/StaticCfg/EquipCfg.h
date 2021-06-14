#pragma once
#include "dbStructDef.h"
#include "ItemDef.h"


struct EquipCfg
{
	Layer layer;
	vector<DbAttr> attrs;

	ItemQuality quality = ItemQuality::Normal;

};


struct EquipCfgMgr
{
	unordered_map<uint16, EquipCfg> m_EquipCfg;
	EquipCfgMgr();
};