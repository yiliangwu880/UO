
#pragma once
#include "AccMgr.h"
#include "MsgDispatch.h"
#include "Verify.h"
#include "AccData.h"
#include "AccSn.h"
#include "Packets.h"



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




