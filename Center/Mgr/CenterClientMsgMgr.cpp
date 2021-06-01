
#include "UoProto.h"
#include "CenterClientMsgMgr.h"
#include "Packets.h"
#include "CfgMgr.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>  
#include "svr_util/include/str_util.h"
#include "libevent_cpp/include/include_all.h"
#include "NetState.h"

using namespace lc;

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
		{
			//无条件认证通过
			VerifyRetStruct d;
			d.is_success = true;
			L_DEBUG("req verify ret ok");
			AccMgr::Ins().ReqVerifyRet(state.m_sn.id, d);
		}
	//	state.Version = new ClientVersion(clientMaj, clientMin, clientRev, clientPat);
	}

	static void AccountLogin(NetState &state, PacketReader &pvSrc)
	{
		//if (state.SentFirstPacket)
		//{
		//	state.Dispose();
		//	return;
		//}

	//	state.SentFirstPacket = true;

		string username = pvSrc.ReadString(30);
		string password = pvSrc.ReadString(30);
		L_INFO("AccountLogin %s %s", username.c_str(), password.c_str());

		//AccountLoginEventArgs e = new AccountLoginEventArgs(state, username, password);

		//EventSink.InvokeAccountLogin(e);

		//if (e.Accepted)
		//{
		//	AccountLogin_ReplyAck(state);
		//}
		//else
		//{
		//	AccountLogin_ReplyRej(state, e.RejectReason);
		//}
		vector<ServerInfo> info;
		ServerInfo i;
		{
#if 0
			//sockaddr_in（在netinet / in.h中定义）：
			struct sockaddr_in {
				short int sin_family;                      /* Address family */
				unsigned short int sin_port;       /* Port number */
				struct in_addr sin_addr;              /* Internet address */
				unsigned char sin_zero[8];         /* Same size as struct sockaddr */
			};
			struct in_addr {
				unsigned long s_addr;
			};

			typedef struct in_addr {
				union {
					struct {
						unsigned char s_b1,
							s_b2,
							s_b3,
							s_b4;
					} S_un_b;
					struct {
						unsigned short s_w1,
							s_w2;
					} S_un_w;
					unsigned long S_addr;
				} S_un;
			} IN_ADDR;

#endif
		}
		info.push_back(CenterMgr::Ins().GetServerInfo());
		AccountLoginAck rsp(info);
		state.CompressionEnabled = false;
		state.Send(rsp);
	}

	static void PlayServer(NetState &state, PacketReader &pvSrc)
	{
		int index = pvSrc.ReadInt16();

		//判断账号，选服合法
		//var info = state.ServerInfo;
		//IAccount a = state.Account;

		//if (info == null || a == null || index < 0 || index >= info.Length)
		//{
		//	Utility.PushColor(ConsoleColor.Red);
		//	Console.WriteLine("Client: {0}: Invalid Server ({1})", state, index);
		//	Utility.PopColor();

		//	state.Dispose();
		//}
		//else
		//{
		//	state.AuthID = GenerateAuthID(state);

		//	state.SentFirstPacket = false;
		//	state.Send(new PlayServerAck(info[index], state.AuthID));
		//}
		PlayServerAck p(CenterMgr::Ins().GetServerInfo(), 1);
		state.CompressionEnabled = false;
		state.Send(p);
	}

	//第二个链接，第一条接收
	static void GameLogin(NetState &state, PacketReader &pvSrc)
	{
		L_DEBUG("GameLogin")
		{
			//无条件认证通过
			VerifyRetStruct d;
			d.is_success = true;
			L_DEBUG("req verify ret ok");
			AccMgr::Ins().ReqVerifyRet(state.m_sn.id, d);
		}
		//state.SentFirstPacket = true;

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
	
	}

}


RegGlobalEvent(EV_SVR_CFG_INI, PacketHandlers::CfgInit);
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
	Register(0x91, 65, false, GameLogin);
}