#pragma once
#include "SubCom.h"

class LoginPlayer : public SubCom
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
	static void ReqLoginZone_sc(CenterCon &con, const proto::ReqLoginZone_sc &msg);
	static void ReqReLoginZone_sc(CenterCon &con, const proto::ReqReLoginZone_sc &msg);

};


