
#include "UoProto.h"
#include "CenterClientMsgMgr.h"

using NetState = const Session &;

namespace
{

	void LoginServerSeed(NetState state, PacketReader pvSrc)
	{

	}
	void CreateCharacter(NetState state, PacketReader pvSrc)
	{

	}
}

RegGlobalEvent(EV_SVR_CFG_INI, PacketHandlers::CfgInit);
void PacketHandlers::CfgInit(bool &ret)
{
	PacketHandlers::Ins().Init();
}

void PacketHandlers::Init()
{
	m_Handlers.resize(numeric_limits<uint8_t>::max());
	Register(0x00, 104, false, CreateCharacter);
	Register(0xEF, 21, false, LoginServerSeed);
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

PacketHandler *PacketHandlers::GetHandler(uint8_t packetID)
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
