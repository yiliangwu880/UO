
#include "CfgMgr.h"
#include "mgr/EventMgr.h"
using namespace std;
using namespace su;

CfgMgr *gCfgMgr = &CfgMgr::Ins();
namespace
{
	bool InitEx()
	{
		L_COND(gCfgMgr->m_centerCfg.LoadFile(), false);
		L_COND(gCfgMgr->m_comCfg.LoadFile(), false);
		return true;
	}
	void InitCfg(bool &ret)
	{
		if (!InitEx())
		{
			ret = false;
		}
	}
	STATIC_RUN(RegEvent<EV_CFG_INI>(InitCfg))
}
