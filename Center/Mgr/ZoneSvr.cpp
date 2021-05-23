#include "CenterMgr.h"
#include "EventMgr.h"
#include "CfgMgr.h"
#include "ZoneSvr.h"

using namespace std;
using namespace su;
using namespace proto;


ZoneSvr * ZoneSvrMgr::FindZoneSvr(uint16 svrId)
{
	return MapFind(m_svrId2Zone, svrId);
}



STATIC_RUN(MsgDispatch<ZoneSvrCon>::Ins().RegMsgHandler(&ZoneSvrMgr::ReqZoneOk_cs));
void ZoneSvrMgr::ReqZoneOk_cs(ZoneSvrCon &con, const ReqZoneOk_cs &msg)
{
	L_INFO("ReqZoneOk_cs");
	ZoneSvr * svr = MapFind(m_svrId2Zone, svrId);
	if (svr != nullptr)
	{
		L_ERROR("repeated reg zone");
		return;
	}
	ZoneSvr &svr = m_svrId2Zone[svrId];
	svr.m_cid = con.GetId();
	svr.m_svrId = msg.svrId;
	CenterMgr::Ins().SetZoneOk(msg.svrId);
}

