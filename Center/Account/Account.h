
#pragma once
#include "dbTableDef.h"
#include "AccMgr.h"
#include "MsgDispatch.h"

class Account
{
	enum State
	{
		None, //初始化状态，刚创建
		WaitVerify, //等查库授权,
		VerifyOk,
	};
	acc::SessionId m_verifySid;
	acc::SessionId m_sid;
	State m_state = None;
	db::Account m_data;
public:
	Account(const string &name);
	void Verify(const acc::SessionId &id, const proto::Login_cs &req);
	void QueryAccCB(bool ret, const db::Account &data);
};




