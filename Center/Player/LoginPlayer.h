#pragma once
#include "ZoneSvr.h"
#include "SubComCenter.h"
#include "dbTableDef.h"

class LoginPlayer : public SubComCenter
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
	State GetState() const { return m_State; }
	void SetState(State state);

	void LoginZone(const DbPlayer &data);
	void ReLogin();
public:
	static void RspLoginZone_cs(ZoneSvrCon &con, const proto::RspLoginZone_cs &msg);
	static void RspReLoginZone_cs(ZoneSvrCon &con, const proto::RspReLoginZone_cs &msg);
};

