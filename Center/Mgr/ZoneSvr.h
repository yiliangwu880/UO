#pragma once
#include "ZoneSvrCon.h"

struct ZoneSvr
{
	uint16 m_svrId;
	uint64 m_cid;
	template<class Msg>
	void Send(const Msg &msg)
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
	ZoneSvr *FindZoneSvr(uint16 svrId);

public:
	static void ReqZoneOk_cs(ZoneSvrCon &con, const ReqZoneOk_cs &msg);
};
