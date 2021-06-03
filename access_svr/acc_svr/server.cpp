#include "server.h"
#include "svr_util/include/read_cfg.h"

using namespace std;
using namespace acc;
using namespace lc;

bool Server::Init()
{
	bool r = m_svr_listener.Init(CfgMgr::Ins().GetInnerPort(), CfgMgr::Ins().GetInnerIp());
	L_COND_F(r);

	r = m_client_listener.Init(CfgMgr::Ins().GetExPort(), CfgMgr::Ins().GetExIp());
	L_COND_F(r);

	L_DEBUG("Server::Init ok");
	return true;
}

ExternalSvrCon * Server::FindClientSvrCon(uint64 cid)
{
	BaseConMgr &conMgr = m_client_listener.GetConnMgr();
	SvrCon *pClient = conMgr.FindConn(cid);
	ExternalSvrCon *p = dynamic_cast<ExternalSvrCon *>(pClient);
	if (nullptr == p)
	{
		L_DEBUG("find ClientSvrCon fail. cid=%lld", cid);
	}
	return p;
}

uint32 Server::GetExConSize() const
{
	return m_client_listener.GetConstConnMgr().GetConSize();
}


