//链接center
#pragma once
#include "CAccMgr.h"
#include "UoProto.h"

class Packet;
struct NetState;
using OnPacketReceive = void(*)(NetState &sn, PacketReader &pvSrc);

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
	
public:
	static void CfgInit(bool &ret);
	void Init();
	//@length 包固定长度。 0表示包是可变长度
	void Register(uint8_t packetID, int length, bool ingame, OnPacketReceive onReceive);
	PacketHandler *GetHandler(uint8_t packetID);
	const std::vector<PacketHandler> &GetHandlers()const  { return m_Handlers; };

private:

};
