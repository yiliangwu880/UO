
#include "UoProto.h"
#include "CenterClientMsgMgr.h"
#include "PacketsC.h"
#include "DynCfgMgr.h"
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
		acc.m_Verify.ReqVerify(state.m_sn.id, password); //验证成功后，发 AccountLoginAck

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

	}


	void SendHexStr(NetState &state, bool isFixed, const char *p)
	{
		LogPacket t(isFixed);
		t.SetHexLog(p);
		state.Send(t);
	}

	//接收 创建角色
	static void CreateCharacter70160(NetState &state, PacketReader &pvSrc)
	{
		shared_ptr<Account> pAcc = state.GetAccount();
		L_COND_V(pAcc);
		L_DEBUG("rev create char, acc=%s", pAcc->Name().c_str());
		DbPlayer player;
		DbActor &playerBase = player.actor;

		int unk1 = pvSrc.ReadInt32();
		int unk2 = pvSrc.ReadInt32();
		int unk3 = pvSrc.ReadByte();
		player.name = pvSrc.ReadString(30);
		player.actor.actorBase.name = player.name;
			
		pvSrc.Seek(2, SeekOrigin::Current);
		int flags = pvSrc.ReadInt32();
		pvSrc.Seek(8, SeekOrigin::Current);
		int prof = pvSrc.ReadByte();
		pvSrc.Seek(15, SeekOrigin::Current);

		int genderRace = pvSrc.ReadByte();

		playerBase.actorAttr.str = pvSrc.ReadByte();
		playerBase.actorAttr.dex = pvSrc.ReadByte();
		playerBase.actorAttr.intl = pvSrc.ReadByte();
		int is1 = pvSrc.ReadByte();
		int vs1 = pvSrc.ReadByte();
		int is2 = pvSrc.ReadByte();
		int vs2 = pvSrc.ReadByte();
		int is3 = pvSrc.ReadByte();
		int vs3 = pvSrc.ReadByte();
		int is4 = pvSrc.ReadByte();
		int vs4 = pvSrc.ReadByte();

		playerBase.actorBase.hue              = pvSrc.ReadUInt16();
		playerBase.actorBase.hairItemID       = pvSrc.ReadInt16();	//hairVal 
		playerBase.actorBase.hairHue          = pvSrc.ReadInt16();	//hairHue 
		playerBase.actorBase.facialHairItemID = pvSrc.ReadInt16();	//hairValf
		playerBase.actorBase.facialHairHue    = pvSrc.ReadInt16();	//hairHuef
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
		playerBase.actorBase.female = female;
		//Race race = null;

		byte raceID = (byte)(genderRace < 4 ? 0 : ((genderRace / 2) - 1));
		playerBase.actorBase.race = raceID;

		static su::IdCreater idCreater;
		player.uin = idCreater.CreateId();
		pAcc->m_AccData.CreatePlayer(player);
	}

	void PlayCharacter(NetState &state, PacketReader &pvSrc)
	{
		pvSrc.ReadInt32(); // 0xEDEDEDED

		string name = pvSrc.ReadString(30);

		pvSrc.Seek(2, SeekOrigin::Current);
		int flags = pvSrc.ReadInt32();
		
		pvSrc.Seek(24, SeekOrigin::Current);
		
		int charSlot = pvSrc.ReadInt32();//idx, start 0
		int clientIP = pvSrc.ReadInt32();

		shared_ptr<Account> a = state.Account();
		L_COND_V(a);
		a->m_AccData.SelectActor(charSlot);

			// Check if anyone is using this account
			//for (int i = 0; i < a.Length; ++i)
			//{
			//	Mobile check = a[i];

			//	if (check != null && check.Map != Map.Internal && check != m)
			//	{
			//		Utility.PushColor(ConsoleColor.Red);
			//		Console.WriteLine("Login: {0}: Account In Use", state);
			//		Utility.PopColor();

			//		state.Send(new PopupMessage(PMMessage.CharInWorld));

			//		return;
			//	}
			//}

			//NetState.ProcessDisposedQueue();

			//state.Flags = (ClientFlags)flags;//0x0000003f

			//state.Mobile = m;
			//m.NetState = state;

			//if (state.Version == null)
			//{
			//	state.Send(new ClientVersionReq());

			//	state.BlockAllPackets = true;

			//	new LoginTimer(state).Start();
			//}
			//else
			//{
			//	DoLogin(state);
			//}
	}

}



void PacketHandlers::Init()
{
	m_Handlers.resize(numeric_limits<uint8_t>::max());
	Register(0xEF, 21, false, LoginServerSeed);
	Register(0x80, 62, false, AccountLogin);
	Register(0xA0, 3, false, PlayServer);
	Register(0x91, 65, false, GameLogin);////第二个链接
	Register(0xF8, 106, false, CreateCharacter70160);
	Register(0x5D, 73, false, PlayCharacter);
}