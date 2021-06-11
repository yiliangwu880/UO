
#include "UoProto.h"
#include "ZoneClientMsgMgr.h"
#include "NetState.h"

namespace
{

	void ExtendedCommand(NetState &state, PacketReader &pvSrc)
	{

	}
	void CreateCharacter(NetState &state, PacketReader &pvSrc)
	{

	}
	void ScreenSize(NetState &state, PacketReader &pvSrc)
	{

	}
}
void PacketHandlers::Init()
{
	m_Handlers.resize(numeric_limits<uint8_t>::max());


	Register(0xBF, 0, true, ExtendedCommand); //16位的消息号，

	////////////////
	RegisterExtended(0x05, false, ScreenSize);

#if 0

	//抄C# ServUO
	Register(0x00, 104, false, CreateCharacter);
	Register(0x01, 5, false, Disconnect);
	Register(0x02, 7, true, MovementReq);
	Register(0x03, 0, true, AsciiSpeech);
	Register(0x04, 2, true, GodModeRequest);
	Register(0x05, 5, true, AttackReq);
	Register(0x06, 5, true, UseReq);
	Register(0x07, 7, true, LiftReq);
	Register(0x08, 14, true, DropReq);
	Register(0x09, 5, true, LookReq);
	Register(0x0A, 11, true, Edit);
	Register(0x12, 0, true, TextCommand);
	Register(0x13, 10, true, EquipReq);
	Register(0x14, 6, true, ChangeZ);
	Register(0x22, 3, true, Resynchronize);
	Register(0x2C, 2, true, DeathStatusResponse);
	Register(0x34, 10, true, MobileQuery);
	Register(0x3A, 0, true, ChangeSkillLock);
	Register(0x3B, 0, true, VendorBuyReply);
	Register(0x47, 11, true, NewTerrain);
	Register(0x48, 73, true, NewAnimData);
	Register(0x58, 106, true, NewRegion);
	Register(0x5D, 73, false, PlayCharacter);
	Register(0x61, 9, true, DeleteStatic);
	Register(0x6C, 19, true, TargetResponse);
	Register(0x6F, 0, true, SecureTrade);
	Register(0x72, 5, true, SetWarMode);
	Register(0x73, 2, false, PingReq);
	Register(0x75, 35, true, RenameRequest);
	Register(0x79, 9, true, ResourceQuery);
	Register(0x7E, 2, true, GodviewQuery);
	Register(0x7D, 13, true, MenuResponse);
	Register(0x80, 62, false, AccountLogin);
	Register(0x83, 39, false, DeleteCharacter);
	Register(0x91, 65, false, GameLogin);
	Register(0x95, 9, true, HuePickerResponse);
	Register(0x96, 0, true, GameCentralMoniter);
	Register(0x98, 0, true, MobileNameRequest);
	Register(0x9A, 0, true, AsciiPromptResponse);
	Register(0x9B, 258, true, HelpRequest);
	Register(0x9D, 51, true, GMSingle);
	Register(0x9F, 0, true, VendorSellReply);
	Register(0xA0, 3, false, PlayServer);
	Register(0xA4, 149, false, SystemInfo);
	Register(0xA7, 4, true, RequestScrollWindow);
	Register(0xAD, 0, true, UnicodeSpeech);
	Register(0xB1, 0, true, DisplayGumpResponse);
	Register(0xB6, 9, true, ObjectHelpRequest);
	Register(0xB8, 0, true, ProfileReq);
	Register(0xBB, 9, false, AccountID);
	Register(0xBD, 0, true, ClientVersion);
	Register(0xBE, 0, true, AssistVersion);
	Register(0xBF, 0, true, ExtendedCommand); //16位的消息号，
	Register(0xC2, 0, true, UnicodePromptResponse);
	Register(0xC8, 2, true, SetUpdateRange);
	Register(0xC9, 6, true, TripTime);
	Register(0xCA, 6, true, UTripTime);
	Register(0xCF, 0, false, AccountLogin);
	Register(0xD0, 0, true, ConfigurationFile);
	Register(0xD1, 2, true, LogoutReq);
	Register(0xD6, 0, true, BatchQueryProperties);
	Register(0xD7, 0, true, EncodedCommand);
	Register(0xE1, 0, false, ClientType);
	Register(0xEC, 0, false, EquipMacro);
	Register(0xED, 0, false, UnequipMacro);
	Register(0xEF, 21, false, LoginServerSeed);
	Register(0xF4, 0, false, CrashReport);
	Register(0xF8, 106, false, CreateCharacter70160);

	Register6017(0x08, 15, true, DropReq6017);
	Register(0x8D, 0, false, ECCreateCharacter);

	RegisterExtended(0x05, false, ScreenSize);
	RegisterExtended(0x06, true, PartyMessage);
	RegisterExtended(0x07, true, QuestArrow);
	RegisterExtended(0x09, true, DisarmRequest);
	RegisterExtended(0x0A, true, StunRequest);
	RegisterExtended(0x0B, false, Language);
	RegisterExtended(0x0C, true, CloseStatus);
	RegisterExtended(0x0E, true, Animate);
	RegisterExtended(0x0F, false, Empty); // What's this?
	RegisterExtended(0x10, true, QueryProperties);
	RegisterExtended(0x13, true, ContextMenuRequest);
	RegisterExtended(0x15, true, ContextMenuResponse);
	RegisterExtended(0x1A, true, StatLockChange);
	RegisterExtended(0x1C, true, CastSpell);
	RegisterExtended(0x24, false, UnhandledBF);
	RegisterExtended(0x2C, true, BandageTarget);

	//#region Stygian Abyss
	RegisterExtended(0x32, true, ToggleFlying);

	RegisterExtended(0x2D, true, TargetedSpell);
	RegisterExtended(0x2E, true, TargetedSkillUse);
	RegisterExtended(0x30, true, TargetByResourceMacro);

	RegisterEncoded(0x19, true, SetAbility);
	RegisterEncoded(0x28, true, GuildGumpRequest);

	RegisterEncoded(0x32, true, QuestGumpRequest);

	////////////from scripte file//////////

	Register(0xFA, 1, true, UOStoreRequest);
	Register(0x66, 0, true,  OnPacketReceive(XmlTextEntryBook.ContentChange));
	Register(0x06, 5, true,  OnPacketReceive(XmlAttach.UseReq));
	Register(0xDA, 0, true,  OnPacketReceive(OnPacket));
	Register(0xD4, 0, true,  OnPacketReceive(HeaderChange));
	Register(0x66, 0, true,  OnPacketReceive(ContentChange));
	Register(0x93, 99, true,  OnPacketReceive(OldHeaderChange));
	Register(0xF1, 0, false,  OnPacketReceive(OnReceive));
	Register(0xB5, 0x40, true, OpenChatWindowRequest);
	Register(0xB3, 0, true, ChatAct);
	Register(0xD9, 0x10C, false, OnReceive);
	Register(0xF0, 0, false,  OnPacketReceive(DecodeBundledPacket));
	Register(0x71, 0, true,  OnPacketReceive(BBClientRequest));
	Register(0x56, 11, true,  OnPacketReceive(OnMapCommand));

	PacketHandlers.RegisterExtended(0x1E, true,  OnPacketReceive(QueryDesignDetails));
	PacketHandlers.RegisterExtended(0x2A, true,  OnPacketReceive(HeritageTransform));
	PacketHandlers.RegisterExtended(0x33, true,  OnPacketReceive(MultiMouseMovementRequest));

	PacketHandlers.RegisterEncoded(0x32, true,  OnEncodedPacketReceive(QuestButton));
	PacketHandlers.RegisterEncoded(0x1E, true,  OnEncodedPacketReceive(EquipLastWeaponRequest));
	PacketHandlers.RegisterEncoded(0x32, true,  OnEncodedPacketReceive(XmlQuest.QuestButton));
	PacketHandlers.RegisterEncoded(0x02, true,  OnEncodedPacketReceive(Designer_Backup));
	PacketHandlers.RegisterEncoded(0x03, true,  OnEncodedPacketReceive(Designer_Restore));
	PacketHandlers.RegisterEncoded(0x04, true,  OnEncodedPacketReceive(Designer_Commit));
	PacketHandlers.RegisterEncoded(0x05, true,  OnEncodedPacketReceive(Designer_Delete));
	PacketHandlers.RegisterEncoded(0x06, true,  OnEncodedPacketReceive(Designer_Build));
	PacketHandlers.RegisterEncoded(0x0C, true,  OnEncodedPacketReceive(Designer_Close));
	PacketHandlers.RegisterEncoded(0x0D, true,  OnEncodedPacketReceive(Designer_Stairs));
	PacketHandlers.RegisterEncoded(0x0E, true,  OnEncodedPacketReceive(Designer_Sync));
	PacketHandlers.RegisterEncoded(0x10, true,  OnEncodedPacketReceive(Designer_Clear));
	PacketHandlers.RegisterEncoded(0x12, true,  OnEncodedPacketReceive(Designer_Level));

	PacketHandlers.RegisterEncoded(0x13, true,  OnEncodedPacketReceive(Designer_Roof)); // Samurai Empire roof
	PacketHandlers.RegisterEncoded(0x14, true,  OnEncodedPacketReceive(Designer_RoofDelete)); // Samurai Empire roof

	PacketHandlers.RegisterEncoded(0x1A, true,  OnEncodedPacketReceive(Designer_Revert));


#endif
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
	m_ExtendedHandlers[packetID] = PacketHandler(packetID, length, ingame, onReceive);
}

PacketHandler *PacketHandlers::GetHandler(uint8_t packetID)
{
	if (packetID >= (int)m_Handlers.size())
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

PacketHandler * PacketHandlers::GetExtendedHandler(uint8_t packetID)
{
	return MapFind(m_ExtendedHandlers, packetID);
}
