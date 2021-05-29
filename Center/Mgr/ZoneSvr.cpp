#include "CenterMgr.h"
#include "EventMgr.h"
#include "CfgMgr.h"
#include "ZoneSvr.h"

using namespace std;
using namespace su;
using namespace proto;

static ZoneSvrMgr &gZoneSvrMgr = ZoneSvrMgr::Ins();

ZoneSvr * ZoneSvrMgr::FindZoneSvr(uint16 svrId)
{
	return MapFind(m_svrId2Zone, svrId);
}



STATIC_RUN(MsgDispatch<ZoneSvrCon>::Ins().RegMsgHandler(&ZoneSvrMgr::ReqZoneOk_cs));
void ZoneSvrMgr::ReqZoneOk_cs(ZoneSvrCon &con, const proto::ReqZoneOk_cs &msg)
{
	L_INFO("ReqZoneOk_cs, zoneId=%d", msg.svrId);
	if (nullptr != MapFind(gZoneSvrMgr.m_svrId2Zone, msg.svrId))
	{
		L_ERROR("repeated reg zone");
		return;
	}
	ZoneSvr &svr = gZoneSvrMgr.m_svrId2Zone[msg.svrId];
	svr.m_cid = con.GetId();
	svr.m_svrId = msg.svrId;
	CenterMgr::Ins().SetZoneOk(msg.svrId);
}

