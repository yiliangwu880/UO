
#include "UoProto.h"
#include "ZoneClientMsgMgr.h"
#include "NetState.h"
#include "Packets.h"



GRegEvent(EV_SVR_CFG_INI, PacketHandlers::CfgInit);
void PacketHandlers::CfgInit(bool &ret)
{
	PacketHandlers::Ins().Init();
}


void PacketHandlers::Register(uint8_t packetID, int length, bool ingame, OnPacketReceive onReceive)
{
	if (0 != m_Handlers[packetID].m_PacketID)
	{
		L_ERROR("repeated reg packetId %d", packetID);
		return;
	}
	m_Handlers[packetID] = PacketHandler(packetID, length, ingame, onReceive);
}

void PacketHandlers::RegisterExtended(uint8_t packetID, bool ingame, OnPacketReceive onReceive)
{
	auto it = m_ExtendedHandlers.find(packetID);
	if (it != m_ExtendedHandlers.end())
	{
		L_ERROR("repeated reg packetId %d", packetID);
		return;
	}
	m_ExtendedHandlers[packetID] = PacketHandler(packetID, 0, ingame, onReceive);
}

PacketHandler *PacketHandlers::GetHandler(uint8_t packetID)
{
	if (packetID >= (uint8_t)m_Handlers.size())
	{
		L_ERROR("unknow packetId 0x%x", packetID);
		return nullptr;
	}
	PacketHandler *p = &m_Handlers[packetID];
	if (p->m_PacketID == 0)
	{
		return nullptr;
	}
	return p;
}

PacketHandler * PacketHandlers::GetExtendedHandler(uint16_t packetID)
{
	return MapFind(m_ExtendedHandlers, packetID);
}

