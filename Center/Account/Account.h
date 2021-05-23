
#pragma once
#include "dbTableDef.h"
#include "AccMgr.h"
#include "MsgDispatch.h"

class Account : public WeakPtr<Account>
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
	acc::SessionId m_sid;
	db::Account m_data;

public:
	Account(const string &name);
	void ReqVerify(const acc::SessionId &id, const proto::Login_cs &req);
	void OnDbLoad(bool ret, const db::Account &data);
	const acc::SessionId &Sid() const { return m_sid.id; }
	const string &Name() const { return m_data.name; }
	void SetVerifyOk(const acc::SessionId &sid);

	static void CreateActor(acc::Session &sn, const proto::CreateActor_cs &msg);
	static void OnInsert(bool ret, const db::Player &data, any para);

	static void SelectActor(acc::Session &sn, const proto::SelectActor_cs &msg);
	static void OnSelect(bool ret, const db::Player &data, any para);
};




