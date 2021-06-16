
#include "UoProto.h"
#include "ZoneClientMsgMgr.h"
#include "NetState.h"
#include "Packets.h"
#include "ZoneMisc.h"


namespace
{

	void ExtendedCommand(NetState &ns, PacketReader &pvSrc)
	{
		int packetID = pvSrc.ReadUInt16();

		PacketHandler *ph = PacketHandlers::Ins().GetExtendedHandler(packetID);
		if (nullptr == ph)
		{
			L_ERROR("find msg handler fail. extended packetId=: 0x%x", packetID);
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

		MovementAck rsp(seq, Notoriety::Innocent);
		state.Send(rsp);
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
	void MobileQuery(NetState &state, PacketReader &pvSrc)
	{
		Mobile *from = state.Mobile();
		L_COND_V(from);

		pvSrc.ReadInt32(); // 0xEDEDEDED
		int type = pvSrc.ReadByte();

		uint32 serial = pvSrc.ReadInt32();
#if 0

		if (Serial::IsMobile(serial))
		{
			if (Mobile *m = World.FindMobile(serial))
			{
				switch (type)
				{
				case 0x00: // Unknown, sent by godclient
				{
					L_ERROR("God Client");
					break;
				}
				case 0x04: // Stats
				{
					m->OnStatsQuery(from);
					break;
				}
				case 0x05:
				{
					m->OnSkillsQuery(from);
					break;
				}
				default:
				{
					pvSrc.Trace(state);
					break;
				}
				}
			}
		}
		else if (Serial::IsItem(serial))
		{
			IDamageable item = World.FindItem(serial) as IDamageable;

			if (item != null)
			{
				switch (type)
				{
				case 0x00:
				{
					if (VerifyGC(state))
					{
						Console.WriteLine("God Client: {0}: Query 0x{1:X2} on {2} '{3}'", state, type, serial, item.Name);
					}

					break;
				}
				case 0x04: // Stats
				{
					item.OnStatsQuery(from);
					break;
				}
				case 0x05:
				{
					break;
				}
				default:
				{
					pvSrc.Trace(state);
					break;
				}
				}
			}
		}


#endif
	}

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
	Register(0x34, 10, true, MobileQuery);

	////////////////
	RegisterExtended(0x05, false, ScreenSize);
	RegisterExtended(0x0B, false, Language);


}