

#include "UoClientMsgMgr.h"

using namespace std;

void PacketHandlers::Init()
{
	m_Handlers.resize(numeric_limits<uint8_t>::max());
	//抄C# ServUO
	Register(0x00, 104, false);
	Register(0x01, 5, false);
	Register(0x02, 7, true);
	Register(0x03, 0, true);
	Register(0x04, 2, true);
	Register(0x05, 5, true);
	Register(0x06, 5, true);
	Register(0x07, 7, true);
	Register(0x08, 14, true);
	Register(0x09, 5, true);
	Register(0x0A, 11, true);
	Register(0x12, 0, true);
	Register(0x13, 10, true);
	Register(0x14, 6, true);
	Register(0x22, 3, true);
	Register(0x2C, 2, true);
	Register(0x34, 10, true);
	Register(0x3A, 0, true);
	Register(0x3B, 0, true);
	Register(0x47, 11, true);
	Register(0x48, 73, true);
	Register(0x58, 106, true);
	Register(0x5D, 73, false);
	Register(0x61, 9, true);
	Register(0x6C, 19, true);
	Register(0x6F, 0, true);
	Register(0x72, 5, true);
	Register(0x73, 2, false);
	Register(0x75, 35, true);
	Register(0x79, 9, true);
	Register(0x7E, 2, true);
	Register(0x7D, 13, true);
	Register(0x80, 62, false);
	Register(0x83, 39, false);
	Register(0x91, 65, false);
	Register(0x95, 9, true);
	Register(0x96, 0, true);
	Register(0x98, 0, true);
	Register(0x9A, 0, true);
	Register(0x9B, 258, true);
	Register(0x9D, 51, true);
	Register(0x9F, 0, true);
	Register(0xA0, 3, false);
	Register(0xA4, 149, false);
	Register(0xA7, 4, true);
	Register(0xAD, 0, true);
	Register(0xB1, 0, true);
	Register(0xB6, 9, true);
	Register(0xB8, 0, true);
	Register(0xBB, 9, false);
	Register(0xBD, 0, true);
	Register(0xBE, 0, true);
	Register(0xBF, 0, true);//16位的消息号， acc不需要进一步处理
	Register(0xC2, 0, true);
	Register(0xC8, 2, true);
	Register(0xC9, 6, true);
	Register(0xCA, 6, true);
	Register(0xCF, 0, false);
	Register(0xD0, 0, true);
	Register(0xD1, 2, true);
	Register(0xD6, 0, true);
	Register(0xD7, 0, true);
	Register(0xE1, 0, false);
	Register(0xEC, 0, false);
	Register(0xED, 0, false);
	Register(0xEF, 21, false);
	Register(0xF4, 0, false);
	Register(0xF8, 106, false);

	//Register6017(0x08, 15, true);
	Register(0x8D, 0, false);

	RegisterExtended(0x05, false);
	RegisterExtended(0x06, true);
	RegisterExtended(0x07, true);
	RegisterExtended(0x09, true);
	RegisterExtended(0x0A, true);
	RegisterExtended(0x0B, false);
	RegisterExtended(0x0C, true);
	RegisterExtended(0x0E, true);
	RegisterExtended(0x0F, false); // What's this?
	RegisterExtended(0x10, true);
	RegisterExtended(0x13, true);
	RegisterExtended(0x15, true);
	RegisterExtended(0x1A, true);
	RegisterExtended(0x1C, true);
	RegisterExtended(0x24, false);
	RegisterExtended(0x2C, true);

	//#region Stygian Abyss
	RegisterExtended(0x32, true);

	RegisterExtended(0x2D, true);
	RegisterExtended(0x2E, true);
	RegisterExtended(0x30, true);

	RegisterEncoded(0x19, true);
	RegisterEncoded(0x28, true);

	RegisterEncoded(0x32, true);

	////////////from scripte file//////////

	Register(0xFA, 1, true);
	Register(0x66, 0, true);
	//Register(0x06, 5, true);
	Register(0xDA, 0, true);
	Register(0xD4, 0, true);
	//Register(0x66, 0, true);
	Register(0x93, 99, true);
	Register(0xF1, 0, false);
	Register(0xB5, 0x40, true);
	Register(0xB3, 0, true);
	Register(0xD9, 0x10C, false);
	Register(0xF0, 0, false);
	Register(0x71, 0, true);
	Register(0x56, 11, true);

}

void PacketHandlers::Register(uint8_t packetID, int length, bool ingame)
{
	if (0 != m_Handlers[packetID].m_PacketID )
	{
		L_ERROR("repeated reg packetId 0x%x", packetID);
		return;
	}
	m_Handlers[packetID] = PacketHandler(packetID, length, ingame);
}


PacketHandler *PacketHandlers::GetHandler(uint8_t packetID)
{
	if (packetID >= (uint8_t)m_Handlers.size())
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
