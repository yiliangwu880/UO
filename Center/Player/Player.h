#pragma once
#include "ZoneSvr.h"

class SceneTran
{
	enum class State
	{
		Playing,
		Moving,
	};
	State m_State;

public:
	State GetState() const { return m_State; }
	void SetState(State val);
};
struct BaseInfo 
{
	uint64 m_uin = 0;
	uint16 m_zoneId = 0;
};
class Player
{
	BaseInfo m_BaseInfo;

public:

	void Init(uint64 uin) {};

	template<class Msg>
	void SendToZone(const Msg &msg)
	{
		ZoneSvr *svr = ZoneSvrMgr::Ins().GetZoneSvr(m_BaseInfo.m_zoneId);
		L_COND_V(svr);
		svr->SendMsg(msg);
	}

private:

};

