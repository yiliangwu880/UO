#include "AccountSubCom.h"

class Verify : public AccountSubCom
{
	enum State
	{
		None,          //初始化状态，刚创建
		WaitDbQuery,   //等查库授权,
		WaitAccVerify, //检验成功
		VerifyOk,      //授权成功，可以收发消息。 有新链接验证通过，--》WaitReplace
		WaitReplace,   //顶号检验成功， 等acc通知授权成功。
	};

	State m_state = None;
	acc::SessionId m_waitVerifySid; //等查库授权 中的sid. 未认证。用来发送失败给客户端
	string m_waitVerifyPsw;
	lc::Timer m_vtm; //verify time out, will del account;

public: 
	Verify(Account &owner)
		:AccountSubCom(owner)
	{
	}
	void ReqVerify(const acc::SessionId &id, CStr &psw);
	void OnDbLoad();
	void SetVerifyOk(const acc::SessionId &sid);
	void GameLogin(const acc::SessionId &sid, CStr &psw);
	void GameLoginOk(const acc::SessionId &sid);
private:
	void OnVerifyTimeOut();

};
