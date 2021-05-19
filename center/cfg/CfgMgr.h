#include "centerCfg.h"
#include "comCfg.h"

class CfgMgr : public Singleton<CfgMgr>
{
public:
	centerCfg m_centerCfg;
	comCfg m_comCfg;
};

extern CfgMgr *gCfgMgr;

