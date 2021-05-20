#include "centerCfg.h"
#include "comCfg.h"

class CfgMgr : public Singleton<CfgMgr>
{
	centerCfg m_centerCfg;
	comCfg m_comCfg;
public:
	const centerCfg &ZoneCfg() const { return m_centerCfg; }
	const comCfg &ComCfg() const { return m_comCfg; }
	bool Init();
};

extern CfgMgr *gCfgMgr;

