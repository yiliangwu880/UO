#pragma once
#include "ZoneSvrCon.h"

struct ZoneSvr
{
	uint16 m_svrId;
	uint64 m_cid;
	template<class Msg>
	void SendMsg(const Msg &msg)
	{
		ZoneSvrCon *con = Svr::Ins().m_Listener.GetConnMgr().FindConn(m_cid);
		L_COND_V(con);
		con->Send(msg);
	}
};

class ZoneSvrMgr : public Singleton<ZoneSvrMgr>
{
	std::unordered_map<uint16, ZoneSvr> m_svrId2Zone;

public:
	ZoneSvr *GetZoneSvr(uint16 svrId);
	ZoneSvr &DoGetZoneSvr(uint16 svrId);
};
