//接入服管理

#pragma once
#include "acc_driver.h"

class Account;
class Player;
struct CenterSnEx : public BaseSnEx
{
	weak_ptr<Account> m_pAccount;
	weak_ptr<Player> m_pPlayer;
};

class AccMgr : public acc::ADFacadeMgr, public Singleton<AccMgr>
{
public:
	void Start();
public:
	virtual void OnRegResult(uint16 svr_id) override;
	virtual void OnRevVerifyReq(const acc::SessionId &id, uint32 cmd, const char *msg, uint16 msg_len) override;
	virtual void OnRevClientMsg(const acc::Session &session, uint32 cmd, const char *msg, uint16 msg_len)  override;

	//client认证成功，创建会话。 概念类似 新socket连接客户端
	virtual void OnClientConnect(const acc::Session &session) override;

};
