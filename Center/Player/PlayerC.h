#pragma once
#include "ZoneSvr.h"
#include "AccMgrC.h"
#include "SceneTranC.h"
#include "LoginPlayerC.h"
#include "CBaseData.h"
#include "PlayerSnC.h"


class PlayerC : public WeakPtr<PlayerC>
{
public:
	BaseData m_BaseData;
	PlayerSnC m_CPlayerSn;
	SceneTranC m_SceneTran;
	LoginPlayerC m_LoginPlayer;

public:
	PlayerC(const DbPlayer &data);

	template<class Msg>
	void SendToZone(const Msg &msg)
	{
		ZoneSvr *svr = ZoneSvrMgr::Ins().FindZoneSvr(m_BaseData.m_zoneId);
		L_COND_V(svr, "zoneid=%d", m_BaseData.m_zoneId);
		svr->Send(msg);
	}

	uint64 Uin() { return m_BaseData.m_uin; }
	const string &Name() { return m_BaseData.name; }
	uint64 ZoneId() {return m_BaseData.m_zoneId;}
public:

private:
};

