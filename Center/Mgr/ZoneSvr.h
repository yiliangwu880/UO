#pragma once
#include "ZoneSvrCon.h"


class Svr : public Singleton<Svr>
{
public:
	lc::Listener<ZoneSvrCon> m_Listener;

public:
	static void Start(bool &ret);
};

struct ZoneSvr
{
	uint16 m_svrId = 0;
	weak_ptr<ZoneSvrCon> m_con;
	template<class Msg>
	void Send(const Msg &msg)
	{
		shared_ptr<ZoneSvrCon> con = m_con.lock();
		L_COND_V(con, "find ZoneSvrCon fail, maybe disconnect。 svrId=%d", m_svrId);
		con->Send(msg);
	}
};

class ZoneSvrMgr : public Singleton<ZoneSvrMgr>
{
	std::unordered_map<uint16, ZoneSvr> m_svrId2Zone;

public:
	ZoneSvr *FindZoneSvr(uint16 svrId);
	void DelZoneSvr(uint16 svrId);

public:
	static void ReqZoneOk_cs(ZoneSvrCon &con, const proto::ReqZoneOk_cs &msg);
};
