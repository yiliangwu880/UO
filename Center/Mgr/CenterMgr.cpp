#include "CenterMgr.h"
#include "GlobalEvent.h"
#include "DynCfgMgr.h"
#include "version.h"
#include "ZoneSvrCon.h"
#include "libevent_cpp/include/include_all.h"
#include "db_driver.h"

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
		TableCfg::Ins(); //触发检查
	}
	STATIC_RUN(RegEvent<EV_SVR_START>(Init));
}

void CenterMgr::Init()
{
	L_INFO("build time %s ", APP_VERSTR);
	for (auto &svrId : gDynCfg.ComCfg().zone.allSvrId)
	{
		m_zoneId2Ok[svrId] = false;
	}
	auto f = [this]()
	{
		L_INFO("on db connect cb");
		m_isDbOk = true;
		checkAllOk();
	};
	Dbproxy::Ins().Init(gDynCfg.ComCfg().dbproxy.ip, gDynCfg.ComCfg().dbproxy.port, f);

	{//init server info
		const char* connect_ip = DynCfgMgr::Ins().ComCfg().access.ex_ip.c_str();
		unsigned short connect_port = DynCfgMgr::Ins().ComCfg().access.ex_port;
		sockaddr_in m_addr;
		memset(&m_addr, 0, sizeof(m_addr));
		m_addr.sin_family = AF_INET;
		m_addr.sin_addr.s_addr = inet_addr(connect_ip);
		m_addr.sin_port = auto_hton(connect_port);

		//L_DEBUG("sin_addr = 0x%x ", *(unsigned long *)&m_addr.sin_addr);
		//L_DEBUG("sin_port = 0x%x ", m_addr.sin_port);
		m_ServerInfo.Address.Address = *(int32 *)&m_addr.sin_addr;
		//L_DEBUG("m_ServerInfo.Address = 0x%x", i.Address);
		m_ServerInfo.Address.Port = connect_port;
	}
	
	L_INFO("CenterMgr::Init");
}

void CenterMgr::SetAccOk()
{
	m_isAccOk = true;
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
	COND_V(m_isAccOk);
	for (auto &v: m_zoneId2Ok)
	{
		COND_V(v.second);
	}
	COND_V(m_isDbOk);
	m_allok = true;
	L_INFO("===========all svr is ready==========");
}

