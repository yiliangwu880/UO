#include "GCfg.h"

ItemCfgMgr::ItemCfgMgr()
	:m_ItemCfg({
			{1, { 1 }},
			{1, { 1 }}
		})
	, m_WeaponCfg({
			{ 1, { 1, WeaponType::BothHand } }
		})
	, m_DressCfg({

			{ 1, { 1,  /*dressIdx */0 } },
			{ 1, { 1344, 0 } },
		})
{}

