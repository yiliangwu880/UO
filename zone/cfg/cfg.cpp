#include "eventMgr.h"
#include "comCfg.h"

using namespace su;

void InitCfg()
{
	comCfg c;
	c.LoadFile();
	L_INFO("c.port=%d", c.port);

}
STATIC_RUN(RegEvent<EV_CFG_INI>(InitCfg))
