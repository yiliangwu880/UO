
#pragma once
#include "dbTableDef.h"
#include "AccMgr.h"
#include "MsgDispatch.h"

class Account
{
	static const int MAX_ACTOR = 4;
	enum State
	{
		None,          //初始化状态，刚创建
		WaitDbQuery,   //等查库授权,
		WaitAccVerify, //检验成功， 等acc通知授权成功。
		VerifyOk,      //授权成功，可以收发消息。 有新链接验证通过，--》WaitReplace
		WaitReplace,   //顶号检验成功， 等acc通知授权成功。
	};

	State m_state = None;
	acc::SessionId m_waitVerifySid; //等查库授权 中的sid. 未认证。用来发送失败给客户端
	string m_waitVerfyPsw;
	acc::Session m_sn;
	db::Account m_data;

public:
	Account(const string &name);
	void ReqVerify(const acc::SessionId &id, const proto::Login_cs &req);
	void OnDbLoad(bool ret, const db::Account &data);
	const acc::SessionId &Sid() const { return m_sn.id; }
	const string &Name() const { return m_data.name; }
	void SetVerifyOk(const acc::Session &sn);

	static void CreateActor(acc::SessionId &sid, const proto::CreateActor_cs &msg);
};




