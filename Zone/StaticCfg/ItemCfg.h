#pragma once

//wait del
enum class ItemType
{
	None,
	Dress, //装备,衣服，可穿戴。
	Weapon, 
};

enum class WeaponType
{
	Primary,
	BothHand, //双手
	Second, //副手
};

struct ItemCfg
{
	uint16 id;
	uint16 hue;
};

struct WeaponCfg
{
	uint16 id;
	WeaponType type;
};

struct DressCfg
{
	uint16 id;
	uint16 dressIdx;//穿那个部位，0 start
};

struct ItemCfgMgr 
{
	unordered_map<uint16, ItemCfg> m_ItemCfg;
	unordered_map<uint16, WeaponCfg> m_WeaponCfg;
	unordered_map<uint16, DressCfg> m_DressCfg;
	ItemCfgMgr();
};