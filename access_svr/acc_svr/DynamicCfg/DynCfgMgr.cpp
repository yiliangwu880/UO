
#include "DynCfgMgr.h"
#include "log_def.h"
using namespace std;
using namespace su;

DynamicCfgMgr &gDynCfg = DynamicCfgMgr::Ins();
bool DynamicCfgMgr::Init()
{
	L_COND(gDynCfg.m_comCfg.LoadFile(), false);
	return true;
}