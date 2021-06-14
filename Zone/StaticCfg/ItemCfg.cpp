#include "GCfg.h"

ItemCfgMgr::ItemCfgMgr()
	:m_ItemCfg({
//axe
{0xF49, { 400, ItemType::Weapon, }},
//ChainChest
{0x13BF, { 700, ItemType::Equip, }},
//shirt
{0x1517, {  100, ItemType::Equip, }},
//bandage
{0xE21, {}},
//bag
{0xE76, {200,ItemType::Container}},
//Backpack
{0xE75, {200,ItemType::Container}}
})
{}

