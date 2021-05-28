#include "ZoneSvrCon.h"
#include "CfgMgr.h"
#include "EventMgr.h"

using namespace lc;
using namespace su;
using namespace proto;

Listener<ZoneSvrCon> gListener;
namespace
{
	void Start(bool &ret)
	{
		if (!gListener.Init(gCfgMgr->ComCfg().center.port))
		{
			ret = false;
		}
	}
	STATIC_RUN(RegEvent<EV_SVR_START>(Start))
}



void ZoneSvrCon::OnRecv(const MsgPack &msg)
{
	MsgDispatch<ZoneSvrCon>::Ins().Dispatch(*this, msg.data, msg.len);
}

void ZoneSvrCon::OnConnected()
{

}


