#include "CenterMgr.h"
#include "EventMgr.h"
#include "CfgMgr.h"
#include "ZoneSvr.h"

using namespace std;
using namespace su;
using namespace proto;

namespace
{
	void HReqZoneOk_cs(ZoneSvrCon &con, const ReqZoneOk_cs &msg)
	{
		L_INFO("HReqZoneOk_cs");
		ZoneSvr &svr = ZoneSvrMgr::Ins().DoGetZoneSvr(msg.svrId);
		svr.m_cid = con.GetId();
		svr.m_svrId = msg.svrId;
		CenterMgr::Ins().SetZoneOk(msg.svrId);
	}
	STATIC_RUN(MsgDispatch<ZoneSvrCon>::Ins().RegMsgHandler(HReqZoneOk_cs));
}

ZoneSvr * ZoneSvrMgr::GetZoneSvr(uint16 svrId)
{
	return MapFind(m_svrId2Zone, svrId);
}

ZoneSvr & ZoneSvrMgr::DoGetZoneSvr(uint16 svrId)
{
	return m_svrId2Zone[svrId];
}

