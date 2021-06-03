
#include "CfgMgr.h"
#include "log_def.h"
using namespace std;
using namespace su;

CfgMgr *gCfgMgr = &CfgMgr::Ins();
bool CfgMgr::Init()
{
	L_COND(gCfgMgr->m_comCfg.LoadFile(), false);
	return true;
}