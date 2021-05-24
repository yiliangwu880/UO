//接入服管理

#pragma once
#include "acc_driver.h"

class Player;
struct ZoneSnEx
{
	weak_ptr<Player> m_pPlayer;
};

class AccMgr : public acc::ADFacadeMgr, public Singleton<AccMgr>
{
public:
	void Start();
	virtual void OnRegResult(uint16 svr_id) override;
	virtual void OnRevClientMsg(const acc::Session &session, uint32 cmd, const char *msg, uint16 msg_len) override;

	virtual void OnMsgRspCacheMsg(const acc::Session &session, bool isCache) override;
};
