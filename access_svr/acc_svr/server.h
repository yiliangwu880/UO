#pragma once
#include <string>
#include <vector>
#include "libevent_cpp/include/include_all.h"
#include "log_def.h"
#include "svr_util/include/singleton.h"
#include "svr_util/include/easy_code.h"
#include "external_con.h"
#include "inner_con.h"
#include "DynamicCfg/DynCfgMgr.h"

class Server: public Singleton<Server>
{
public:
	bool Init();
	ExternalSvrCon *FindClientSvrCon(uint64 cid);
	uint32 GetExConSize() const;//外部连接数量
public:
	lc::Listener<InnerSvrCon> m_svr_listener;
	lc::Listener<ExternalSvrCon> m_client_listener;
};

