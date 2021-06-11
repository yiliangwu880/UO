//接入服管理

#pragma once
#include "acc_driver.h"

class Player;
using WeakPlayer = weak_ptr<Player>;

class Player;
struct ZoneSnEx
{
	weak_ptr<Player> m_pPlayer;

};

class AccMgr : public acc::ADFacadeMgr, public Singleton<AccMgr>
{
public:
	static void Start(bool &ret);
	Player *GetPlayer(const acc::Session &sn);

public:

	virtual void OnRegResult(uint16 svr_id) override;
	virtual void OnRevClientMsg(const acc::Session &sn, uint32 cmd, const char *msg, uint16 msg_len) override;

	virtual void OnMsgRspCacheMsg(const acc::Session &sn, bool isCache) override;

	//client断线通知
	virtual void OnClientDisCon(const acc::Session &sn) override;
	//当设置uin,accName
	virtual void OnRevBroadcastUinToSession(const acc::Session &session) override;
};
