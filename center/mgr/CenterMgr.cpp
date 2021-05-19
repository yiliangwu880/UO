#include "CenterMgr.h"
#include "mgr/EventMgr.h"
#include "cfg/CfgMgr.h"
#include "version.h"

using namespace std;
using namespace su;

namespace
{
	void Init(bool &ret)
	{
		CenterMgr::Ins().Init();
	}
	STATIC_RUN(RegEvent<EV_START>(Init))
}

void CenterMgr::Init()
{
	L_INFO("build time %s ", APP_VERSTR);
	for (auto &svrId : gCfgMgr->m_comCfg.zone.allSvrId)
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
