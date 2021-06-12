#include "ItemMgr.h"

ItemBase::ItemBase(uint16 cfgId)
{
	static uint32 seedId = 0;
	seedId++;
	m_id = seedId;
	const ItemCfg *p = gCfg.GetItemCfg(cfgId);
	if (nullptr == p)
	{
		p = gCfg.GetItemCfg(0);
	}
	m_cfg = p;
}
