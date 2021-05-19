#include "ZoneMgr.h"
#include "EventMgr.h"
#include "CfgMgr.h"

using namespace std;
using namespace su;

namespace
{
	void Init(bool &ret)
	{
		//ZoneMgr::Ins().Init();
	}
	STATIC_RUN(RegEvent<EV_START>(Init))
}



