#include "eventMgr.h"
#include "CC_centerCfg.h"

using namespace su;

void InitCfg()
{
	centerCfg c;
	c.LoadFile();
	L_INFO("c.a=%d", c.a);

}
STATIC_RUN(RegEvent<EV_CFG_INI>(InitCfg))
