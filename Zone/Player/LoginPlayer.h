#pragma once
#include "BaseData.h"

class LoginPlayer : public PlayerSubCom
{
	enum State
	{
		LoginOk,
		OffLine,
	};
	State m_State = LoginOk;

public:
	LoginPlayer(Player &owner)
		:PlayerSubCom(owner)
	{}
	State State() const { return m_State; }

	void SendLogin();
	void ClientDisCon();

public:
	static void ReqLoginZone_sc(CenterCon &con, const proto::ReqLoginZone_sc &msg);
	static void ReqReLoginZone_sc(CenterCon &con, const proto::ReqReLoginZone_sc &msg);

};


