#pragma once
#include "dbStructDef.h"
#include "ItemDef.h"



struct WeaponCfg
{
	Layer layer;
	vector<DbAttr> attrs;

	ItemQuality quality = ItemQuality::Normal;
	int32 strReq = -1;
	int32 dexReq = -1;
	int32 intReq = -1;
	int32 hitSound = -1;
	int32 missSound = -1;
	int32 speed = -1;
	int32 maxRange = -1;
};

struct WeaponCfgMgr
{
	unordered_map<uint16, WeaponCfg> m_WeaponCfg;
	WeaponCfgMgr();
};