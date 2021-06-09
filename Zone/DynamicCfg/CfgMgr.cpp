
#include "CfgMgr.h"
#include "GlobalEvent.h"
using namespace std;
using namespace su;

const CfgMgr &gCfgMgr = CfgMgr::Ins();
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
	L_COND(CfgMgr::Ins().m_zoneCfg.LoadFile(), false);
	L_COND(CfgMgr::Ins().m_comCfg.LoadFile(), false);
	return true;
}