#pragma once
#include "AccountSubCom.h"
#include "ComPackets.h"


//first connect session, for server list
class FirstSn : public AccountSubCom
{
	SessionId sid;
	bool Seeded = false;
	uint32 Seed = 0;
	bool compressionEnabled = true;

public:
	FirstSn(Account &owner)
		:AccountSubCom(owner)
	{
	}

	void SetSessionId(const acc::SessionId &id) { sid = id; };
	void Send(Packet &packet);
	void Dispose(); //save as Disconnect
	void Disconnect(); //
	void SetCompressionEnabled(bool val) { compressionEnabled = val; }
};

//account session
class AccSn : public AccountSubCom
{
	SessionId sid;
	bool Seeded = false;
	uint32 Seed = 0;
	bool compressionEnabled = true;

public:
	AccSn(Account &owner)
		:AccountSubCom(owner)
	{
	}

	void SetSessionId(const acc::SessionId &id) { sid = id; };
	void Send(Packet &packet);
	void Dispose(); //save as Disconnect
	void Disconnect(); //
	void SetCompressionEnabled(bool val) { compressionEnabled = val; }
};
