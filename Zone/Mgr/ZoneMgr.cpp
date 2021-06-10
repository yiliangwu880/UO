#include "ZoneMgr.h"
#include "GlobalEvent.h"
#include "DynCfgMgr.h"
#include "version.h"
#include "db_driver.h"

using namespace std;
using namespace su;
//using namespace proto;

namespace
{
	void Start(bool &ret)
	{
	}
}



STATIC_RUN(RegEvent<EV_SVR_START>(&ZoneMgr::Start))
void ZoneMgr::Start(bool &ret)
{
	L_INFO("%s", APP_VERSTR);
	Dbproxy::Ins().Init(gDynCfg.ComCfg().dbproxy.ip, gDynCfg.ComCfg().dbproxy.port);
}
