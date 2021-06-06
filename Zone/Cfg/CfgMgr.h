#include "zoneCfg.h"
#include "comCfg.h"

class CfgMgr : public Singleton<CfgMgr>
{
	zoneCfg m_zoneCfg;
	comCfg m_comCfg;

public:
	bool Init();
	const zoneCfg &ZoneCfg() const { return m_zoneCfg; }
	const comCfg &ComCfg() const { return m_comCfg; }
};

extern const CfgMgr &gCfgMgr;

