#include "ZoneMgr.h"
#include "EventMgr.h"
#include "CfgMgr.h"
#include "version.h"

using namespace std;
using namespace su;
//using namespace proto;

namespace
{
	void Start(bool &ret)
	{
		L_INFO("%s", APP_VERSTR);
		//ZoneMgr::Ins().Start();
	}
	STATIC_RUN(RegEvent<EV_START>(Start))
}



