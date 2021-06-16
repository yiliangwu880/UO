#pragma once
#include "BaseData.h"
#include "Packets.h"
#include "NetState.h"

class PlayerSn : public PlayerSubCom<PlayerSn>
{
	acc::SessionId m_sid;
public:
	NetState m_ns; //simulate c#

public:
	PlayerSn(Player &owner)
		:PlayerSubCom(owner)
	{
	}

	const acc::SessionId &GetSid() const { return m_sid; }
	void SetSid(const acc::SessionId &val) { m_sid = val; }
	void Send(Packet &packet);
	void Dispose(); //save as Disconnect
	void Disconnect(); //
};


