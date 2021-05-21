
#pragma once
#include "dbTableDef.h"
#include "AccMgr.h"
#include "MsgDispatch.h"

class Account
{
	enum State
	{
		None,          //初始化状态，刚创建
		WaitDbQuery,   //等查库授权,
		WaitAccVerify, //检验成功，设置SessionId, 等acc通知授权成功。
		VerifyOk,      //授权成功，可以收发消息。
	};
	acc::SessionId m_waitVerifySid; //等查库授权 中的sid. 未认证。用来发送失败给客户端
	acc::Session m_sn;
	State m_state = None;
	db::Account m_data;
public:
	Account(const string &name);
	void ReqVerify(const acc::SessionId &id, const proto::Login_cs &req);
	void QueryAccCB(bool ret, const db::Account &data);
	const acc::SessionId &Sid() const { return m_sn.id; }
	const string &Name() const { return m_data.name; }
	void SetVerifyOk(const acc::Session &sn);
};




