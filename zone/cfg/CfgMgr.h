#include "zoneCfg.h"
#include "comCfg.h"

class CfgMgr : public Singleton<CfgMgr>
{
	zoneCfg m_zoneCfg;
	comCfg m_comCfg;
public:
	zoneCfg ZoneCfg() const { return m_zoneCfg; }
	comCfg ComCfg() const { return m_comCfg; }
};

extern CfgMgr *gCfgMgr;

