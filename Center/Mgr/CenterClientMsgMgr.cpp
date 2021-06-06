
#include "UoProto.h"
#include "CenterClientMsgMgr.h"
#include "CPackets.h"
#include "CfgMgr.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>  
#include "svr_util/include/str_util.h"
#include "libevent_cpp/include/include_all.h"
#include "NetState.h"
#include "Account/AccountMgr.h"

using namespace lc;
//c#适配
#define byte uint8_t

namespace
{

	static void LoginServerSeed(NetState &state, PacketReader &pvSrc)
	{
		state.Seed = pvSrc.ReadUInt32();
		state.Seeded = true;

		if (state.Seed == 0)
		{
			L_ERROR("Login: Invalid Client");
			state.Dispose();
			return;
		}

		int clientMaj = pvSrc.ReadInt32();
		int clientMin = pvSrc.ReadInt32();
		int clientRev = pvSrc.ReadInt32();
		int clientPat = pvSrc.ReadInt32();

	}

	static void AccountLogin(NetState &state, PacketReader &pvSrc)
	{
		string username = pvSrc.ReadString(30);
		string password = pvSrc.ReadString(30);
		L_INFO("AccountLogin %s %s", username.c_str(), password.c_str());

		Account &acc = AccountMgr::Ins().DoGetAcc(username);
		acc.m_Verify.ReqVerify(state.m_sn.id, password);

#if 0

		vector<ServerInfo> info;
		ServerInfo i;

		info.push_back(CenterMgr::Ins().GetServerInfo());
		AccountLoginAck rsp(info);
		state.CompressionEnabled = false;
		state.Send(rsp);
#endif
	}

	//选服请求 
	static void PlayServer(NetState &state, PacketReader &pvSrc)
	{
		//无条件通过，发送唯一服务器地址给客户端
		int index = pvSrc.ReadInt16();
		PlayServerAck p(CenterMgr::Ins().GetServerInfo(), 1);
		state.CompressionEnabled = false;
		state.Send(p);
	}

	//第二个链接，第一条接收
	static void GameLogin(NetState &state, PacketReader &pvSrc)
	{
		L_DEBUG("GameLogin")
		//{
		//	//无条件认证通过
		//	VerifyRetStruct d;
		//	d.is_success = true;
		//	L_DEBUG("req verify ret ok");
		//	AccMgr::Ins().ReqVerifyRet(state.m_sn.id, d);
		//}

		uint32 authID = pvSrc.ReadUInt32();
#if 0
		if (m_AuthIDWindow.ContainsKey(authID))
		{
			AuthIDPersistence ap = m_AuthIDWindow[authID];
			m_AuthIDWindow.Remove(authID);

			state.Version = ap.Version;
		}
		else if (m_ClientVerification)
		{
			Utility.PushColor(ConsoleColor.Red);
			Console.WriteLine("Login: {0}: Invalid Client", state);
			Utility.PopColor();

			state.Dispose();
			return;
		}

		if (state.AuthID != 0 && authID != state.AuthID)
		{
			Utility.PushColor(ConsoleColor.Red);
			Console.WriteLine("Login: {0}: Invalid Client", state);
			Utility.PopColor();

			state.Dispose();
			return;
		}

		if (state.AuthID == 0 && authID != state.Seed)
		{
			Utility.PushColor(ConsoleColor.Red);
			Console.WriteLine("Login: {0}: Invalid Client", state);
			Utility.PopColor();

			state.Dispose();
			return;
		}
#endif
		string username = pvSrc.ReadString(30);
		string password = pvSrc.ReadString(30);

		Account *acc = AccountMgr::Ins().GetAcc(username);
		L_COND_V(acc);
		acc->m_Verify.GameLogin(state.m_sn.id, password);
#if 0

		// 接受登录
		//state.CityInfo = e.CityInfo;
		SupportedFeatures sf;
		state.Send(sf);

		//if (state.NewCharacterList)
		//{
			CharacterList cl;
			state.Send(cl);
		//}
		//else
		//{
		//	state.Send(new CharacterListOld(state.Account, state.CityInfo));
		//}

#endif
	}


	void EasyMsg123(NetState &state, bool isFixed, const char *p)
	{
		LogPacket t(isFixed);
		t.SetHexLog(p);
		state.Send(t);
	}
	static void DoLogin(NetState &s)
	{
		//临时复制C#响应
		EasyMsg123(s, 1, "1B 0 0 0 5D 0 0 0 0 1 90 D AF A E 0 E 0 0 FF FF FF FF 0 0 0 0 1C 0 10 0 0 0 0 0 0 0 ");
		//EasyMsg123(s, true, "");
		EasyMsg123(s, 0, "BF 0 0 0 8 1");
		EasyMsg123(s, 0, "BF 0 0 0 18 0 0 0 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");

		EasyMsg123(s, 1, "B9 0 FF 92 DB");

		EasyMsg123(s, 0, "78 0 0 0 0 0 5F 1 90 D AF A E E 0 83 EA 10 3 40 0 4 43 E 75 15 0 0 40 0 4 48 13 CC D 0 0 40 0 4 4A 1F 3 16 6 BA 40 0 4 4D 13 FF 1 0 0 40 0 4 4F 15 17 5 0 3 40 0 4 50 15 39 4 0 3 40 0 4 51 17 F 3 6 D1 7F FF FA 83 20 3B B 4 4E 7F FF FA 81 3B 49 F 83 EA 0 0 0 0 ");
		EasyMsg123(s, 1, "20 0 0 0 5F 1 90 0 83 EA 10 D AF A E 0 0 0 E ");
		EasyMsg123(s, 0, "78 0 0 0 0 0 5F 1 90 D AF A E E 0 83 EA 10 3 40 0 4 43 E 75 15 0 0 40 0 4 48 13 CC D 0 0 40 0 4 4A 1F 3 16 6 BA 40 0 4 4D 13 FF 1 0 0 40 0 4 4F 15 17 5 0 3 40 0 4 50 15 39 4 0 3 40 0 4 51 17 F 3 6 D1 7F FF FA 83 20 3B B 4 4E 7F FF FA 81 3B 49 F 83 EA 0 0 0 0 ");
		EasyMsg123(s, 0, "17 0 0 0 0 0 5F 0 1 0 1 0");
		EasyMsg123(s, 0, "17 0 0 0 0 0 5F 0 1 0 2 0 ");
		EasyMsg123(s, 1, "DC 0 0 0 5F 43 58 46 7C ");
		EasyMsg123(s, 1, "4F C ");
		EasyMsg123(s, 1, "4E 0 0 0 5F 0 ");
		EasyMsg123(s, 1, "55");
		EasyMsg123(s, 0, "78 0 0 0 0 0 5F 1 90 D AF A E E 0 83 EA 10 3 40 0 4 43 E 75 15 0 0 40 0 4 48 13 CC D 0 0 40 0 4 4A 1F 3 16 6 BA 40 0 4 4D 13 FF 1 0 0 40 0 4 4F 15 17 5 0 3 40 0 4 50 15 39 4 0 3 40 0 4 51 17 F 3 6 D1 7F FF FA 83 20 3B B 4 4E 7F FF FA 81 3B 49 F 83 EA 0 0 0 0");
		EasyMsg123(s, 0, "11 0 0 0 0 0 5F 61 62 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 48 0 48 0 6 0 0 2D 0 23 0 A 0 23 0 23 0 A 0 A 0 0 3 E8 0 2 0 3D 1 1 1 0 E1 0 5 0 4 0 3 0 3 0 3 0 0 0 F 0 16 0 0 0 0 0 64 0 64 0 64 0 64 0 64 0 0 0 2D 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
		EasyMsg123(s, 1, "72 0 0 32 0");
		EasyMsg123(s, 1, "BC 0 1");
		EasyMsg123(s, 1, "5B B 19 1D");
		EasyMsg123(s, 0, "BF 0 0 0 8 1 ");
		EasyMsg123(s, 0, "DD 0 0 0 0 0 3 B5 A1 58 8D 0 0 0 0 0 0 0 0 0 0 0 8F 0 0 1 33 78 9C 65 CE 51 E 83 20 C 6 E0 1D A5 47 A0 A5 28 5C 67 C6 6C 26 22 66 E2 1E 66 76 F7 51 59 30 68 1A E0 4F DA 2F 74 83 29 F8 F0 EE E1 BB A5 D4 8D 61 F9 C7 57 BF C 9F 3D E7 34 F 1D A8 54 4E 2B 5 9C E B1 34 EF 6B 8C 61 2 92 42 6C E5 B2 80 69 E A5 FB 8C 7E 7C AC 7E 6 4A F3 D0 28 79 73 1D D4 AA AB AD B1 B3 5 E3 9 23 1B D1 6C 64 1F 83 7B 9F 2A 8C E 8B A6 93 26 DD 5C FE E6 7A 6F C3 45 EB AC 6F 3F 5 F7 50 FA 0 0 0 4 0 0 0 5F 0 0 1 68 78 9C 63 D0 61 B0 61 48 62 B0 3 92 4E C 8E C C1 C AE C 6E C FE C 7E C 21 C A C CE 40 96 F 10 7 31 D8 32 28 33 18 0 A1 9 83 21 98 B6 8B 89 4B 50 7 EA D1 C7 D0 65 7 16 5 99 48 A6 C9 75 47 A6 C9 D3 C6 E4 54 B3 E6 ED B4 31 39 ED 4B A4 14 7E 93 1 3F E0 32 D3");
		EasyMsg123(s, 1, "4E 0 0 0 5F 0 ");
		EasyMsg123(s, 0, "AE 0 0 FF FF FF FF FF FF 0 3 B2 0 3 45 4E 55 0 53 79 73 74 65 6D 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 57 0 65 0 6C 0 63 0 6F 0 6D 0 65 0 2C 0 20 0 61 0 62 0 21 0 20 0 54 0 68 0 65 0 72 0 65 0 20 0 69 0 73 0 20 0 63 0 75 0 72 0 72 0 65 0 6E 0 74 0 6C 0 79 0 20 0 31 0 20 0 75 0 73 0 65 0 72 0 20 0 6F 0 6E 0 6C 0 69 0 6E 0 65 0 2C 0 20 0 77 0 69 0 74 0 68 0 20 0 39 0 39 0 32 0 20 0 69 0 74 0 65 0 6D 0 73 0 20 0 61 0 6E 0 64 0 20 0 39 0 35 0 20 0 6D 0 6F 0 62 0 69 0 6C 0 65 0 73 0 20 0 69 0 6E 0 20 0 74 0 68 0 65 0 20 0 77 0 6F 0 72 0 6C 0 64 0 2E 0 0 ");
		EasyMsg123(s, 0, "AE 0 0 FF FF FF FF FF FF 0 3 B2 0 3 45 4E 55 0 53 79 73 74 65 6D 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 54 0 68 0 65 0 20 0 70 0 61 0 67 0 65 0 20 0 71 0 75 0 65 0 75 0 65 0 20 0 69 0 73 0 20 0 65 0 6D 0 70 0 74 0 79 0 2E 0 0");
		EasyMsg123(s, 0, "78 0 0 0 0 0 5F 1 90 D AF A E E 0 83 EA 10 3 40 0 4 43 E 75 15 0 0 40 0 4 48 13 CC D 0 0 40 0 4 4A 1F 3 16 6 BA 40 0 4 4D 13 FF 1 0 0 40 0 4 4F 15 17 5 0 3 40 0 4 50 15 39 4 0 3 40 0 4 51 17 F 3 6 D1 7F FF FA 83 20 3B B 4 4E 7F FF FA 81 3B 49 F 83 EA 0 0 0 0");
		EasyMsg123(s, 0, "17 0 0 0 0 0 5F 0 1 0 1 0");
		EasyMsg123(s, 0, "17 0 0 0 0 0 5F 0 1 0 2 0 ");
		EasyMsg123(s, 1, "2E 40 0 4 51 17 F 0 3 0 0 0 5F 6 D1 ");


#if 0
		Mobile m;

		state.Send(new LoginConfirm(m));

		if (m.Map != null)
		{
			state.Send(new MapChange(m));
		}

		state.Send(new MapPatches());

		{
			SupportedFeatures t;
			state.Send(t);
		}

		state.Sequence = 0;

		{
			MobileIncoming t;
			state.Send(t);
		}

		if (state.NewMobileIncoming)
		{
			state.Send(new MobileUpdate(m));
		}
		else if (state.StygianAbyss)
		{
			state.Send(new MobileUpdate(m));
		}
		else
		{
			state.Send(new MobileUpdateOld(m));
		}

		m.SendEverything();

		m.CheckLightLevels(true);

		state.Send(LoginComplete.Instance);

		state.Send(MobileIncoming.Create(state, m, m));

		state.Send(new MobileStatus(m, m));

		state.Send(Network.SetWarMode.Instantiate(m.Warmode));

		state.Send(SeasonChange.Instantiate(m.GetSeason(), true));

		state.Send(new CurrentTime());

		state.Send(new MapChange(m));

		EventSink.InvokeLogin(new LoginEventArgs(m));

		Console.WriteLine("Client: {0}: Entered World ({1})", state, m);

		m.SendEverything();
		m.ClearFastwalkStack();
#endif
	}


	//接收 创建角色
	static void CreateCharacter70160(NetState &state, PacketReader &pvSrc)
	{
		shared_ptr<Account> pAcc = state.GetAccount();
		L_COND_V(pAcc);
		L_DEBUG("rev create char, acc=%s", pAcc->Name().c_str());
		DbPlayer player;
		DbActor &playerBase = player.base;

		int unk1 = pvSrc.ReadInt32();
		int unk2 = pvSrc.ReadInt32();
		int unk3 = pvSrc.ReadByte();
		player.name = pvSrc.ReadString(30);

		pvSrc.Seek(2, SeekOrigin::Current);
		int flags = pvSrc.ReadInt32();
		pvSrc.Seek(8, SeekOrigin::Current);
		int prof = pvSrc.ReadByte();
		pvSrc.Seek(15, SeekOrigin::Current);

		int genderRace = pvSrc.ReadByte();

		playerBase.str = pvSrc.ReadByte();
		playerBase.dex = pvSrc.ReadByte();
		playerBase.intl = pvSrc.ReadByte();
		int is1 = pvSrc.ReadByte();
		int vs1 = pvSrc.ReadByte();
		int is2 = pvSrc.ReadByte();
		int vs2 = pvSrc.ReadByte();
		int is3 = pvSrc.ReadByte();
		int vs3 = pvSrc.ReadByte();
		int is4 = pvSrc.ReadByte();
		int vs4 = pvSrc.ReadByte();

		playerBase.hue      = pvSrc.ReadUInt16();
		playerBase.hairVal  = pvSrc.ReadInt16();
		playerBase.hairHue  = pvSrc.ReadInt16();
		playerBase.hairValf = pvSrc.ReadInt16();
		playerBase.hairHuef = pvSrc.ReadInt16();
		pvSrc.ReadByte();
		int cityIndex = pvSrc.ReadByte();
		int charSlot = pvSrc.ReadInt32();
		int clientIP = pvSrc.ReadInt32();
		int shirtHue = pvSrc.ReadInt16();
		int pantsHue = pvSrc.ReadInt16();

		/*
		0x00, 0x01
		0x02, 0x03 -> Human Male, Human Female
		0x04, 0x05 -> Elf Male, Elf Female
		0x05, 0x06 -> Gargoyle Male, Gargoyle Female
		*/

		bool female = ((genderRace % 2) != 0);
		playerBase.female = female;
		//Race race = null;

		byte raceID = (byte)(genderRace < 4 ? 0 : ((genderRace / 2) - 1));
		playerBase.race = raceID;
		//race = Race.Races[raceID];

		//if (race == null)
		//{
		//	race = Race.DefaultRace;
		//}

		//var info = state.CityInfo;
		//IAccount a = state.Account;

		//if (info == null || a == null || cityIndex < 0 || cityIndex >= info.Length)
		//{
		//	L_ERROR("");
		//	state.Dispose();
		//}
		//else
		{
#if 0

			// Check if anyone is using this account
			//for (int i = 0; i < a.Length; ++i)
			//{
			//	Mobile check = a[i];

			//	if (check != null && check.Map != Map.Internal)
			//	{
			//		Utility.PushColor(ConsoleColor.Red);
			//		Console.WriteLine("Login: {0}: Account in use", state);
			//		Utility.PopColor();
			//		state.Send(new PopupMessage(PMMessage.CharInWorld));
			//		return;
			//	}
			//}

			state.Flags = (ClientFlags)flags;

			CharacterCreatedEventArgs args = new CharacterCreatedEventArgs(
				state,
				a,
				name,
				female,
				hue,
				str,
				dex,
				intl,
				info[cityIndex],
				new SkillNameValue[4]
				{
					new SkillNameValue((SkillName)is1, vs1), new SkillNameValue((SkillName)is2, vs2),
					new SkillNameValue((SkillName)is3, vs3), new SkillNameValue((SkillName)is4, vs4),
				},
				shirtHue,
				pantsHue,
				hairVal,
				hairHue,
				hairValf,
				hairHuef,
				prof,
				race);

			if (state.Version == null)
			{
				state.Send(new ClientVersionReq());

				state.BlockAllPackets = true;
			}

			EventSink.InvokeCharacterCreated(args);

			Mobile m = args.Mobile;
			if (m != null)
			{
				state.Mobile = m;
				m.NetState = state;

				if (state.Version == null)
				{
					new LoginTimer(state).Start();
				}
				else
				{
					DoLogin(state);
				}
			}
			else
			{
				state.BlockAllPackets = false;
				state.Dispose();
			}

#endif

			static su::IdCreater idCreater;
			player.uin = idCreater.CreateId();
			pAcc->m_AccData.CreatePlayer(player);

			//DoLogin(state); //tmp code
		}
	}

}


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


void PacketHandlers::Init()
{
	m_Handlers.resize(numeric_limits<uint8_t>::max());
	Register(0xEF, 21, false, LoginServerSeed);
	Register(0x80, 62, false, AccountLogin);
	Register(0xA0, 3, false, PlayServer);
	Register(0x91, 65, false, GameLogin);////第二个链接
	Register(0xF8, 106, false, CreateCharacter70160);
}