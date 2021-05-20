#include "CenterMgr.h"
#include "EventMgr.h"
#include "CfgMgr.h"
#include "version.h"
#include "ZoneSvrCon.h"

using namespace std;
using namespace su;
using namespace proto;

namespace
{
	void Init(bool &ret)
	{
		MsgMgr::Check();
		CenterMgr::Ins().Init();
	}
	STATIC_RUN(RegEvent<EV_START>(Init));

	void HReqZoneOk_cs(ZoneSvrCon &con, const ReqZoneOk_cs &msg)
	{
		L_INFO("HReqZoneOk_cs");
		CenterMgr::Ins().SetZoneOk(msg.svrId);
	}
	STATIC_RUN(MsgDispatch<ZoneSvrCon>::Ins().RegMsgHandler(HReqZoneOk_cs));

}

void CenterMgr::Init()
{
	L_INFO("build time %s ", APP_VERSTR);
	for (auto &svrId : gCfgMgr->ComCfg().zone.allSvrId)
	{
		m_zoneId2Ok[svrId] = false;
	}
	L_INFO("CenterMgr::Init");
}

void CenterMgr::SetCenterOk()
{
	m_isCenterOk = true;
	checkAllOk();
}

void CenterMgr::SetZoneOk(uint16 svrId)
{
	auto it = m_zoneId2Ok.find(svrId);
	if (it == m_zoneId2Ok.end())
	{
		L_ERROR("error svrId %d", svrId);
		return;
	}
	it->second = true;
	checkAllOk();
}

void CenterMgr::checkAllOk()
{
	COND_V(m_isCenterOk);
	for (auto &v: m_zoneId2Ok)
	{
		COND_V(v.second);
	}
	m_allok = true;
	L_INFO("all svr is ready");
}
