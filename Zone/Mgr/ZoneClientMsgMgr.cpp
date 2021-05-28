
#include "UoProto.h"
#include "ZoneClientMsgMgr.h"

using NetState = const Session &;

namespace
{

	void CreateCharacter(NetState state, PacketReader pvSrc)
	{

	}

}
void PacketHandlers::Init()
{
	m_Handlers.resize(256);
	Register(0x00, 104, false, CreateCharacter);
}

void PacketHandlers::Register(int packetID, int length, bool ingame, OnPacketReceive onReceive)
{
	if (packetID >= (int)m_Handlers.size())
	{
		L_ERROR("packetId overload %d", packetID);
		return;
	}
	m_Handlers[packetID] = PacketHandler(packetID, length, ingame, onReceive);
}

PacketHandler *PacketHandlers::GetHandler(int packetID)
{
	if (packetID >= (int)m_Handlers.size())
	{
		L_ERROR("packetId overload %d", packetID);
		return nullptr;
	}
	PacketHandler *p = &m_Handlers[packetID];
	if (p->m_PacketID == 0)
	{
		return nullptr;
	}
	return p;
}