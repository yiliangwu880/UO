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
	bool Reset(uint64 cid);
	const acc::SessionId &GetSid() const { return m_sid; }
	void Send(Packet &packet);
	void Dispose(); //save as Disconnect
	void Disconnect(); //


};


