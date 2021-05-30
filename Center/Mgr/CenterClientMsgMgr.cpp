
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
		i.Name = "mytest";
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
			const char* connect_ip = CfgMgr::Ins().ComCfg().access.ip.c_str();
			unsigned short connect_port = CfgMgr::Ins().ComCfg().access.port;
			sockaddr_in m_addr;

			memset(&m_addr, 0, sizeof(m_addr));
			m_addr.sin_family = AF_INET;
			m_addr.sin_addr.s_addr = inet_addr(connect_ip);
			m_addr.sin_port = auto_hton(connect_port);

			L_DEBUG("sin_addr = %x ", *(unsigned long *)&m_addr.sin_addr);
			L_DEBUG("sin_port = %x ", m_addr.sin_port);
			i.Address = *(uint32 *)&m_addr.sin_addr;
			L_DEBUG("i.Address = %x", i.Address);
		}
		info.push_back(i);
		AccountLoginAck rsp(info);
		state.Send(rsp);
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
	Register(0xEF, 21, false, LoginServerSeed);
	Register(0x80, 62, false, AccountLogin);
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

void NetState::Dispose()
{
	AccMgr::Ins().DisconClient(m_sn.id);
}

void NetState::Send(Packet &packet)
{
	L_DEBUG("Send client len=%d, %s", packet.m_Stream.m_Stream.length(), StrUtil::BinaryToHex(packet.m_Stream.m_Stream).c_str());
	AccMgr::Ins().SendToClient(m_sn.id, 0, packet.m_Stream.m_Stream.c_str(), packet.m_Stream.m_Stream.Length());
}
