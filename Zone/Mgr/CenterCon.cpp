#include "CenterCon.h"
#include "CfgMgr.h"
#include "EventMgr.h"
#include "MsgDispatch.h"

using namespace lc;
using namespace su;
using namespace proto;


namespace
{
	void Start(bool &ret)
	{
		bool r = CenterCon::Ins().ConnectInit(gCfgMgr->ComCfg().center.ip.c_str(), gCfgMgr->ComCfg().center.port);
		if (!r)
		{
			L_ERROR("CenterCon::Ins().ConnectInit fail");
			ret = false;
		}
	}
	STATIC_RUN(RegEvent<EV_SVR_START>(Start));


	

}



void CenterCon::OnRecv(const MsgPack &msg)
{
	MsgDispatch<CenterCon>::Ins().Dispatch(*this, msg.data, msg.len);
}

void CenterCon::OnConnected()
{
	ReqZoneOk_cs req;
	req.svrId = gCfgMgr->ZoneCfg().svrId;
	Send(req);
}

void CenterCon::OnDisconnected()
{
}

//for tmp test
static void Hanlder1(CenterCon &con, const RspZoneOk_sc &msg)
{
	L_INFO("Hanlder1");
}
STATIC_RUN(MsgDispatch<CenterCon>::Ins().RegMsgHandler(Hanlder1));

