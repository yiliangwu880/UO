#include "GCfg.h"

const GCfg &gCfg = GCfg::Ins();

const ItemCfg * GCfg::GetItemCfg(uint16 id)
{
	return MapFind(ItemCfgMgr::Ins().m_ItemCfg, id);
}
