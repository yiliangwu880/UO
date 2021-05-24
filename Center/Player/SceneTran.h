#pragma once
#include "ZoneSvr.h"
#include "SubComCenter.h"

class SceneTran : public SubComCenter
{
	enum State
	{
		Playing,       //zone游戏中
		Moving,        //zone切换中
	};
	State m_State = Playing;
public:
	State State() const { return m_State; }
	void State(State state);

public:
	static void ReqZoneReserve(ZoneSvrCon &con, const proto::ReqZoneReserve &msg);
	static void RspZoneReserve(ZoneSvrCon &con, const proto::RspZoneReserve &msg);
	static void ReqTranZone(ZoneSvrCon &con, const proto::ReqTranZone &msg);
};

