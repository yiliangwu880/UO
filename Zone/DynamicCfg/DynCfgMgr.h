//类json动态配置
#include "zoneCfg.h"
#include "comCfg.h"

class DynCfgMgr : public Singleton<DynCfgMgr>
{
	zoneCfg m_zoneCfg;
	comCfg m_comCfg;

public:
	bool Init();
	const zoneCfg &ZoneCfg() const { return m_zoneCfg; }
	const comCfg &ComCfg() const { return m_comCfg; }
};

extern const DynCfgMgr &gDynCfg;

