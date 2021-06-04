
#include "CfgMgr.h"
#include "Mgr/EventMgr.h"
using namespace std;
using namespace su;

const CfgMgr &gCfgMgr = CfgMgr::Ins();
const comCfg::S_testCfg &gTestCfg = CfgMgr::Ins().ComCfg().testCfg;

namespace
{
	void InitCfg(bool &ret)
	{
		if (!CfgMgr::Ins().Init())
		{
			ret = false;
		}
	}
	STATIC_RUN(RegEvent<EV_SVR_CFG_INI>(InitCfg))
}

bool CfgMgr::Init()
{
	L_COND(CfgMgr::Ins().m_centerCfg.LoadFile(), false);
	L_COND(CfgMgr::Ins().m_comCfg.LoadFile(), false);
	return true;
}