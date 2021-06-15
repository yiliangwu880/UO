
#include "UoProto.h"
#include "ZoneClientMsgMgr.h"
#include "NetState.h"
#include "Packets.h"

namespace
{

	void ExtendedCommand(NetState &ns, PacketReader &pvSrc)
	{
		int packetID = pvSrc.ReadUInt16();

		PacketHandler *ph = PacketHandlers::Ins().GetExtendedHandler(packetID);
		if (nullptr == ph)
		{
			L_ERROR("rev unknow extended packetId: 0x%x", packetID);
			return;
		}

		ph->m_OnReceive(ns, pvSrc);
	}

	void CreateCharacter(NetState &state, PacketReader &pvSrc)
	{

	}
	void ScreenSize(NetState &state, PacketReader &pvSrc)
	{
		int width = pvSrc.ReadInt32();
		int unk = pvSrc.ReadInt32();
	}
	void PingReq(NetState &state, PacketReader &pvSrc)
	{
		PingAck rsp(pvSrc.ReadByte());
		state.Send(rsp);
	}

	void MovementReq(NetState &state, PacketReader &pvSrc)
	{
		Direction dir = (Direction)pvSrc.ReadByte();
		int seq = pvSrc.ReadByte();
		int key = pvSrc.ReadInt32();

		Mobile *m = state.Mobile();

		//if ((state.Sequence == 0 && seq != 0) || !m.Move(dir))
		//{
		//	state.Send(new MovementRej(seq, m));
		//	state.Sequence = 0;

		//	m.ClearFastwalkStack();
		//}
		//else
		//{
		//	++seq;

		//	if (seq == 256)
		//	{
		//		seq = 1;
		//	}

		//	state.Sequence = seq;
		//}
	}
	void Language(NetState &state, PacketReader &pvSrc)
	{
		string lang = pvSrc.ReadString(4);

		//if (state.Mobile != null)
		//{
		//	state.Mobile.Language = lang;
		//}
	}
	void AssistVersion(NetState &state, PacketReader &pvSrc)
	{
		int unk = pvSrc.ReadInt32();
		string av = pvSrc.ReadString();
	}

	void ClientVersion(NetState &state, PacketReader &pvSrc)
	{
		//CV version = state.Version = new CV(pvSrc.ReadString());

		//EventSink.InvokeClientVersionReceived(new ClientVersionReceivedArgs(state, version));
	}
	void LookReq(NetState &state, PacketReader &pvSrc)
	{
		//if (state.Mobile != null)
		//{
		////	HandleSingleClick(state.Mobile, World.FindEntity(pvSrc.ReadInt32()));
		//}
	}
}

GRegEvent(EV_SVR_CFG_INI, PacketHandlers::CfgInit);
void PacketHandlers::CfgInit(bool &ret)
{
	PacketHandlers::Ins().Init();
}

void PacketHandlers::Init()
{
	m_Handlers.resize(numeric_limits<uint8_t>::max());


	Register(0x73, 2, false, PingReq);
	Register(0xBF, 0, true, ExtendedCommand); //16位的消息号，
	Register(0x02, 7, true, MovementReq);
	Register(0xBD, 0, true, ClientVersion);
	Register(0xBE, 0, true, AssistVersion);
	Register(0x09, 5, true, LookReq);
	//Register(0x34, 10, true, MobileQuery);

	////////////////
	RegisterExtended(0x05, false, ScreenSize);
	RegisterExtended(0x0B, false, Language);


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
