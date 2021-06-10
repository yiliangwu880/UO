
#include "DynCfgMgr.h"
#include "GlobalEvent.h"
using namespace std;
using namespace su;

const DynCfgMgr &gDynCfg = DynCfgMgr::Ins();
namespace
{
	void InitCfg(bool &ret)
	{
		if (!DynCfgMgr::Ins().Init())
		{
			ret = false;
		}
	}
	STATIC_RUN(RegEvent<EV_SVR_CFG_INI>(InitCfg))
}

bool DynCfgMgr::Init()
{
	L_COND(DynCfgMgr::Ins().m_zoneCfg.LoadFile(), false);
	L_COND(DynCfgMgr::Ins().m_comCfg.LoadFile(), false);
	return true;
}