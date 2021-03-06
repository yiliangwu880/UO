//链接center
#pragma once
#include "ZoneAccMgr.h"
#include "PacketsBase.h"

struct NetState;
using OnPacketReceive = void (*)(NetState &state, PacketReader &pvSrc);

struct PacketHandler
{
	int m_PacketID=0;
	int m_Length=0;
	bool m_Ingame=false;
	OnPacketReceive m_OnReceive=nullptr;
	PacketHandler() {};
	PacketHandler(int packetID, int length, bool ingame, OnPacketReceive onReceive)
	{
		m_PacketID = packetID;
		m_Length = length;
		m_Ingame = ingame;
		m_OnReceive = onReceive;
	}
};

class PacketHandlers : public Singleton<PacketHandlers>
{
	std::vector<PacketHandler> m_Handlers;
	unordered_map<uint16_t, PacketHandler> m_ExtendedHandlers;
public:
	static void CfgInit(bool &ret);

public:
	void Init();
	//@length 包固定长度。 0表示包是可变长度
	void Register(uint8_t packetID, int length, bool ingame, OnPacketReceive onReceive);
	void RegisterExtended(uint8_t packetID, bool ingame, OnPacketReceive onReceive);
	PacketHandler *GetHandler(uint8_t packetID);
	PacketHandler *GetExtendedHandler(uint16_t packetID);

private:

};
