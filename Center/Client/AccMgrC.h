//接入服管理

#pragma once
#include "acc_driver.h"

class Account;
class PlayerC;
struct CenterSnEx
{
	weak_ptr<Account> m_pAccount;
	weak_ptr<PlayerC> m_pPlayer;

};

class AccMgrC : public acc::ADFacadeMgr, public Singleton<AccMgrC>
{
public:
	static void Start(bool &ret);
public:
	virtual void OnRegResult(uint16 svr_id) override;
	virtual void OnRevVerifyReq(const acc::SessionId &id, uint32 cmd, const char *msg, uint16 msg_len) override;
	virtual void OnRevClientMsg(const acc::Session &sn, uint32 cmd, const char *msg, uint16 msg_len)  override;

	//client认证成功，创建会话。 概念类似 新socket连接客户端
	virtual void OnClientConnect(const acc::Session &session) override;

	//当设置uin,accName
	virtual void OnRevBroadcastUinToSession(const acc::Session &session) override;		
	//client断线通知
	virtual void OnClientDisCon(const acc::Session &session) override;
};
