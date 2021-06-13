#pragma once
#include "dbStructDef.h"


struct ItemCfg
{
	uint16 id;
	uint32 weight; //400 == 4.00 石
	ItemType type;
	uint16 hue;

};

struct EquipCfg
{
	uint16 itemId; //ItemCfg id
	Layer layer;
	vector<DbAttr> attrs;


};

struct WeaponCfg
{
	uint16 itemId; //ItemCfg id
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

//暂时没用。衣服也用Equip
struct DressCfg
{
	uint16 id;
	uint16 dressIdx;//穿那个部位，0 start
};

struct ItemCfgMgr 
{
	unordered_map<uint16, ItemCfg> m_ItemCfg;
	unordered_map<uint16, EquipCfg> m_EquipCfg;
	unordered_map<uint16, WeaponCfg> m_WeaponCfg;
	ItemCfgMgr();
};