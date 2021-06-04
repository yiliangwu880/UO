
#pragma once
#include "CAccMgr.h"
#include "MsgDispatch.h"
#include "Verify.h"
#include "AccData.h"
#include "AccSn.h"
#include "CPackets.h"



class Account : public WeakPtr<Account>
{

public:
	Verify m_Verify;
	AccData m_AccData;
	FirstSn m_FirstSn;
	AccSn m_AccSn;

public:
	Account(const string &name);
	const string &Name() const;
	void Send(Packet &packet);

private:

};




