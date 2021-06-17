#pragma once
#include "AccountSubCom.h"
#include "PacketsBase.h"


//first connect session, for server list
class FirstSn : public AccountSubCom
{
	SessionId m_sid;
	bool Seeded = false;
	uint32 Seed = 0;
	bool compressionEnabled = true;

public:
	FirstSn(Account &owner)
		:AccountSubCom(owner)
	{
	}

	void SetSessionId(const acc::SessionId &id) { m_sid = id; };
	void Send(Packet &packet);
	void Dispose(); //save as Disconnect
	void Disconnect(); //
	void SetCompressionEnabled(bool val) { compressionEnabled = val; }
};

//account session
class AccSn : public AccountSubCom
{
	SessionId m_sid;
	bool Seeded = false;
	uint32 Seed = 0;
	bool compressionEnabled = true;

public:
	AccSn(Account &owner)
		:AccountSubCom(owner)
	{
	}

	void SetSessionId(const acc::SessionId &id) { m_sid=id; }
	void Send(Packet &packet);
	void Dispose(); //save as Disconnect
	void Disconnect(); //
	void SetCompressionEnabled(bool val) { compressionEnabled = val; }
	const acc::SessionId &GetSid() const { return m_sid; }
	const Session *GetSn();
	void SendMessage(HueColor hue, CStr &text);
};
