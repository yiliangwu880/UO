#pragma once
#include "log_def.h"
#include "acc_driver.h"

class Packet;
class Player;
class Actor;
//适配C# 写法
struct NetState
{
	const acc::Session *m_sn = nullptr;
	acc::ADFacadeMgr &m_accMgr;
	bool CompressionEnabled = true;
	bool IsEnhancedClient = false;

	NetState(const acc::Session & sn);
	NetState();
	void Init(const acc::Session & sn);

	void Dispose();
	void Send(Packet &packet);
	shared_ptr<Player> GetPlayer();
	Actor *Mobile();

};


