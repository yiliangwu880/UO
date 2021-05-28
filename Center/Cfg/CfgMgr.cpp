
#include "CfgMgr.h"
#include "Mgr/EventMgr.h"
using namespace std;
using namespace su;

CfgMgr *gCfgMgr = &CfgMgr::Ins();
namespace
{
	void InitCfg(bool &ret)
	{
		if (!gCfgMgr->Init())
		{
			ret = false;
		}
	}
	STATIC_RUN(RegEvent<EV_SVR_CFG_INI>(InitCfg))
}

bool CfgMgr::Init()
{
	L_COND(gCfgMgr->m_centerCfg.LoadFile(), false);
	L_COND(gCfgMgr->m_comCfg.LoadFile(), false);
	return true;
}