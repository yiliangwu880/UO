#pragma once
#include "ZoneSvr.h"

class LoginPlayer : public PlayerSubCom
{
	enum State
	{
		None,
		WaitLogin,
		LoginOk,
		WaitReLogin,
	};
	State m_State = None;

public:
	State State() const { return m_State; }
	void State(State state);

	void LoginZone(const db::Player &data);
	void ReLogin();
public:
	static void RspLoginZone_cs(ZoneSvrCon &con, const proto::ReqZoneReserve &msg);
	static void RspReLoginZone_cs(ZoneSvrCon &con, const proto::RspReLoginZone_cs &msg);
};

