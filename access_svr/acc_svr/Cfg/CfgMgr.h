#pragma once
#include "comCfg.h"
#include "libevent_cpp/include/include_all.h"
#include "svr_util/include/singleton.h"
#include "svr_util/include/easy_code.h"

class CfgMgr : public Singleton<CfgMgr>
{
	comCfg m_comCfg;
public:
	const comCfg &ComCfg() const { return m_comCfg; }
	bool Init();

	unsigned short GetInnerPort() const { return m_comCfg.access.inner_port; }
	const char *GetInnerIp() const { return m_comCfg.access.inner_ip.c_str(); }
	unsigned short GetExPort() const { return m_comCfg.access.ex_port; }
	const char *GetExIp() const { return m_comCfg.access.ex_ip.c_str(); }
};

extern CfgMgr &gCfgMgr;

