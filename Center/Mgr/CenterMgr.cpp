#include "CenterMgr.h"
#include "EventMgr.h"
#include "CfgMgr.h"
#include "version.h"
#include "ZoneSvrCon.h"
#include "libevent_cpp/include/include_all.h"

using namespace std;
using namespace su;
using namespace proto;
using namespace lc;

namespace
{
	void Init(bool &ret)
	{
		MsgMgr::Check();
		CenterMgr::Ins().Init();
	}
	STATIC_RUN(RegEvent<EV_SVR_START>(Init));
}

void CenterMgr::Init()
{
	L_INFO("build time %s ", APP_VERSTR);
	for (auto &svrId : gCfgMgr->ComCfg().zone.allSvrId)
	{
		m_zoneId2Ok[svrId] = false;
	}
	{//init server info
		const char* connect_ip = CfgMgr::Ins().ComCfg().access.ip.c_str();
		unsigned short connect_port = CfgMgr::Ins().ComCfg().access.port;
		sockaddr_in m_addr;
		memset(&m_addr, 0, sizeof(m_addr));
		m_addr.sin_family = AF_INET;
		m_addr.sin_addr.s_addr = inet_addr(connect_ip);
		m_addr.sin_port = auto_hton(connect_port);

		//L_DEBUG("sin_addr = %x ", *(unsigned long *)&m_addr.sin_addr);
		//L_DEBUG("sin_port = %x ", m_addr.sin_port);
		m_ServerInfo.Address.Address = *(int32 *)&m_addr.sin_addr;
		//L_DEBUG("m_ServerInfo.Address = %x", i.Address);
		m_ServerInfo.Address.Port = connect_port;
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

