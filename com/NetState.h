#pragma once
#include "log_def.h"
#include "acc_driver.h"

class Packet;
//适配C# 写法, 临时用，等删掉
struct NetState
{
	const acc::Session &m_sn;
	acc::ADFacadeMgr &m_accMgr;
	bool Seeded = false;
	uint32 Seed = 0;
	bool CompressionEnabled = true;

	NetState(const acc::Session & sn, acc::ADFacadeMgr &accMgr);

	void Dispose();
	void Send(Packet &packet);
};


