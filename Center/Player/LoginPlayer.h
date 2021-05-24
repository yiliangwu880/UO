#pragma once
#include "ZoneSvr.h"

class LoginPlayer : public PlayerSubCom
{
	enum State
	{
		WaitLogin,
		LoginOk,
		WaitReLogin,
	};
	State m_State = WaitLogin;

public:
	State State() const { return m_State; }
	void State(State state);

public:
	static void RspLoginZone_cs(ZoneSvrCon &con, const proto::ReqZoneReserve &msg);
};

