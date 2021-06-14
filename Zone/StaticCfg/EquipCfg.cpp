#include "GCfg.h"

EquipCfgMgr::EquipCfgMgr()
	:m_EquipCfg({
	//ChainChest
			{ 0x13BF, { Layer::Shirt,
		{{Attr::MinDam, 1}, {Attr::MaxDam, 1}} }
		},
		//shirt
				{ 0x1517, { Layer::Shirt,
			{} }
			},
		})
	
{}

