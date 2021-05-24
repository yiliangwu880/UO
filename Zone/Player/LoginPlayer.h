#pragma once
#include "ZoneSvr.h"

class LoginPlayer : public PlayerSubCom
{
	enum State
	{
		LoginOk,
		OffLine,
	};
	State m_State = LoginOk;

public:
	State State() const { return m_State; }

	void ClientDisCon();

public:
	static void ReqLoginZone_sc(ZoneSvrCon &con, const proto::ReqLoginZone_sc &msg);
	static void ReqReLoginZone_sc(ZoneSvrCon &con, const proto::ReqReLoginZone_sc &msg);

};


