#pragma once
#include "ItemCfg.h"
//game cfg
class GCfg : public Singleton<GCfg>
{
	
public:
	const ItemCfg *GetItemCfg(uint16 id);
};
extern const GCfg &gCfg;

