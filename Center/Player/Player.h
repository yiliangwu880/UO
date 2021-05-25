#pragma once
#include "ZoneSvr.h"
#include "AccMgr.h"
#include "SceneTran.h"
#include "LoginPlayer.h"


struct BaseData 
{
	uint64 m_uin = 0;
	uint16 m_zoneId = 0;
	uint32 m_sceneId = 0;
	string name;
};

class Player : public WeakPtr<Player>
{
	acc::SessionId m_sid;

public:
	BaseData m_BaseData;
	SceneTran m_SceneTran;
	LoginPlayer m_LoginPlayer;

public:

	void Init(uint64 uin) {};

	template<class Msg>
	void SendToZone(const Msg &msg)
	{
		ZoneSvr *svr = ZoneSvrMgr::Ins().FindZoneSvr(m_BaseData.m_zoneId);
		L_COND_V(svr);
		svr->Send(msg);
	}
	void SetSid(const acc::SessionId &sid);

	uint64 Uin() { return m_BaseData.m_uin; }
	const string &Name() { return m_BaseData.name; }
	uint64 ZoneId() {return m_BaseData.m_zoneId;}
	uint64 Cid() { return m_sid.cid; }
public:

private:
};

