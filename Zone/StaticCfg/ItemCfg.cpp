#include "GCfg.h"

ItemCfgMgr::ItemCfgMgr()
	:m_ItemCfg({
	//axe
			{0xF49, { 0xF49, 400, ItemType::Equip, }},
			//bag
			{1, { 1 }}
		})
	, m_EquipCfg({
	//axe
			{ 0xF49, { 0xF49, Layer::TwoHanded,
		{{Attr::MinDam, 1}, {Attr::MaxDam, 1}} }
		},
		})
	, m_WeaponCfg({
	//axe
			{ 0xF49, { 0xF49, Layer::TwoHanded,
		{{Attr::MinDam, 1}, {Attr::MaxDam, 1}} }
		},
		})
{}

