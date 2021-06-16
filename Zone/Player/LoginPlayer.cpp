#include "PlayerMgr.h"

using namespace proto;
using namespace acc;

namespace
{
	 void DoLogin(Player &m_owner)
	{
		//临时复制C#响应
		m_owner.SendHexStr( 1, "1B 0 0 0 5F 0 0 0 0 1 90 D AF A E 0 E 0 0 FF FF FF FF 0 0 0 0 1C 0 10 0 0 0 0 0 0 0 ");
		//EasyMsg123(s, true, "");
		m_owner.SendHexStr( 0, "BF 0 0 0 8 1");
		m_owner.SendHexStr( 0, "BF 0 0 0 18 0 0 0 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");

		m_owner.SendHexStr( 1, "B9 0 FF 92 DB");

		m_owner.SendHexStr( 0, "78 0 0 0 0 0 5F 1 90 D AF A E E 0 83 EA 10 3 40 0 4 43 E 75 15 0 0 40 0 4 48 13 CC D 0 0 40 0 4 4A 1F 3 16 6 BA 40 0 4 4D 13 FF 1 0 0 40 0 4 4F 15 17 5 0 3 40 0 4 50 15 39 4 0 3 40 0 4 51 17 F 3 6 D1 7F FF FA 83 20 3B B 4 4E 7F FF FA 81 3B 49 F 83 EA 0 0 0 0 ");
		m_owner.SendHexStr( 1, "20 0 0 0 5F 1 90 0 83 EA 10 D AF A E 0 0 0 E ");
		m_owner.SendHexStr( 0, "78 0 0 0 0 0 5F 1 90 D AF A E E 0 83 EA 10 3 40 0 4 43 E 75 15 0 0 40 0 4 48 13 CC D 0 0 40 0 4 4A 1F 3 16 6 BA 40 0 4 4D 13 FF 1 0 0 40 0 4 4F 15 17 5 0 3 40 0 4 50 15 39 4 0 3 40 0 4 51 17 F 3 6 D1 7F FF FA 83 20 3B B 4 4E 7F FF FA 81 3B 49 F 83 EA 0 0 0 0 ");
		m_owner.SendHexStr( 0, "17 0 0 0 0 0 5F 0 1 0 1 0");
		m_owner.SendHexStr( 0, "17 0 0 0 0 0 5F 0 1 0 2 0 ");
		m_owner.SendHexStr( 1, "DC 0 0 0 5F 43 58 46 7C ");
		m_owner.SendHexStr( 1, "4F C ");
		m_owner.SendHexStr( 1, "4E 0 0 0 5F 0 ");
		m_owner.SendHexStr( 1, "55");
		m_owner.SendHexStr( 0, "78 0 0 0 0 0 5F 1 90 D AF A E E 0 83 EA 10 3 40 0 4 43 E 75 15 0 0 40 0 4 48 13 CC D 0 0 40 0 4 4A 1F 3 16 6 BA 40 0 4 4D 13 FF 1 0 0 40 0 4 4F 15 17 5 0 3 40 0 4 50 15 39 4 0 3 40 0 4 51 17 F 3 6 D1 7F FF FA 83 20 3B B 4 4E 7F FF FA 81 3B 49 F 83 EA 0 0 0 0");
		m_owner.SendHexStr( 0, "11 0 0 0 0 0 5F 61 62 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 48 0 48 0 6 0 0 2D 0 23 0 A 0 23 0 23 0 A 0 A 0 0 3 E8 0 2 0 3D 1 1 1 0 E1 0 5 0 4 0 3 0 3 0 3 0 0 0 F 0 16 0 0 0 0 0 64 0 64 0 64 0 64 0 64 0 0 0 2D 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
		m_owner.SendHexStr( 1, "72 0 0 32 0");
		m_owner.SendHexStr( 1, "BC 0 1");
		m_owner.SendHexStr( 1, "5B B 19 1D");
		m_owner.SendHexStr( 0, "BF 0 0 0 8 1 ");
		m_owner.SendHexStr( 0, "DD 0 0 0 0 0 3 B5 A1 58 8D 0 0 0 0 0 0 0 0 0 0 0 8F 0 0 1 33 78 9C 65 CE 51 E 83 20 C 6 E0 1D A5 47 A0 A5 28 5C 67 C6 6C 26 22 66 E2 1E 66 76 F7 51 59 30 68 1A E0 4F DA 2F 74 83 29 F8 F0 EE E1 BB A5 D4 8D 61 F9 C7 57 BF C 9F 3D E7 34 F 1D A8 54 4E 2B 5 9C E B1 34 EF 6B 8C 61 2 92 42 6C E5 B2 80 69 E A5 FB 8C 7E 7C AC 7E 6 4A F3 D0 28 79 73 1D D4 AA AB AD B1 B3 5 E3 9 23 1B D1 6C 64 1F 83 7B 9F 2A 8C E 8B A6 93 26 DD 5C FE E6 7A 6F C3 45 EB AC 6F 3F 5 F7 50 FA 0 0 0 4 0 0 0 5F 0 0 1 68 78 9C 63 D0 61 B0 61 48 62 B0 3 92 4E C 8E C C1 C AE C 6E C FE C 7E C 21 C A C CE 40 96 F 10 7 31 D8 32 28 33 18 0 A1 9 83 21 98 B6 8B 89 4B 50 7 EA D1 C7 D0 65 7 16 5 99 48 A6 C9 75 47 A6 C9 D3 C6 E4 54 B3 E6 ED B4 31 39 ED 4B A4 14 7E 93 1 3F E0 32 D3");
		m_owner.SendHexStr( 1, "4E 0 0 0 5F 0 ");
		m_owner.SendHexStr( 0, "AE 0 0 FF FF FF FF FF FF 0 3 B2 0 3 45 4E 55 0 53 79 73 74 65 6D 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 57 0 65 0 6C 0 63 0 6F 0 6D 0 65 0 2C 0 20 0 61 0 62 0 21 0 20 0 54 0 68 0 65 0 72 0 65 0 20 0 69 0 73 0 20 0 63 0 75 0 72 0 72 0 65 0 6E 0 74 0 6C 0 79 0 20 0 31 0 20 0 75 0 73 0 65 0 72 0 20 0 6F 0 6E 0 6C 0 69 0 6E 0 65 0 2C 0 20 0 77 0 69 0 74 0 68 0 20 0 39 0 39 0 32 0 20 0 69 0 74 0 65 0 6D 0 73 0 20 0 61 0 6E 0 64 0 20 0 39 0 35 0 20 0 6D 0 6F 0 62 0 69 0 6C 0 65 0 73 0 20 0 69 0 6E 0 20 0 74 0 68 0 65 0 20 0 77 0 6F 0 72 0 6C 0 64 0 2E 0 0 ");
		m_owner.SendHexStr( 0, "AE 0 0 FF FF FF FF FF FF 0 3 B2 0 3 45 4E 55 0 53 79 73 74 65 6D 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 54 0 68 0 65 0 20 0 70 0 61 0 67 0 65 0 20 0 71 0 75 0 65 0 75 0 65 0 20 0 69 0 73 0 20 0 65 0 6D 0 70 0 74 0 79 0 2E 0 0");
		m_owner.SendHexStr( 0, "78 0 0 0 0 0 5F 1 90 D AF A E E 0 83 EA 10 3 40 0 4 43 E 75 15 0 0 40 0 4 48 13 CC D 0 0 40 0 4 4A 1F 3 16 6 BA 40 0 4 4D 13 FF 1 0 0 40 0 4 4F 15 17 5 0 3 40 0 4 50 15 39 4 0 3 40 0 4 51 17 F 3 6 D1 7F FF FA 83 20 3B B 4 4E 7F FF FA 81 3B 49 F 83 EA 0 0 0 0");
		m_owner.SendHexStr( 0, "17 0 0 0 0 0 5F 0 1 0 1 0");
		m_owner.SendHexStr( 0, "17 0 0 0 0 0 5F 0 1 0 2 0 ");
		m_owner.SendHexStr( 1, "2E 40 0 4 51 17 F 0 3 0 0 0 5F 6 D1 ");

	}


}
void LoginPlayer::Login()
{
	Scene &scene = SceneMgr::Ins().GetWorld(MapId::Felucca);
	m_owner.m_Actor.EnterScene(scene);
	m_owner.FireEvent<EV_BEFORE_LOGIN>(); 
	SendLogin();
	//DoLogin(m_owner);
}

void LoginPlayer::SendLogin()
{
	L_DEBUG("SendLogin");
	{
		LoginConfirm rsp(m_owner.m_Actor);
		m_owner.Send(rsp);
	}
	{
		MapChange rsp(m_owner.m_Actor);
		m_owner.Send(rsp);
		//state.Send(new MapPatches());
		m_owner.SendHexStr(0, "BF 0 0 0 18 0 0 0 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
		//state.Send(SupportedFeatures.Instantiate(state));
		m_owner.SendHexStr(1, "B9 0 FF 92 DB");
	}
	{
		MobileIncoming rsp(m_owner.m_Actor, m_owner.m_Actor);
		m_owner.Send(rsp);

	}
	{
		MobileUpdate rsp(m_owner.m_Actor);
		m_owner.Send(rsp);
	}
	//m.SendEverything();

	//m.CheckLightLevels(true);
	{
		GlobalLightLevel rsp(1);
		m_owner.Send(rsp);
	}
	{
		PersonalLightLevel rsp(m_owner.m_Actor, 0);
		m_owner.Send(rsp);
	}
	{
		LoginComplete rsp;
		m_owner.Send(rsp);
	}
	{//为什么重复发一次？待分析
		MobileIncoming rsp(m_owner.m_Actor, m_owner.m_Actor);
		m_owner.Send(rsp);
	} 
	{
		MobileStatus rsp(m_owner.m_Actor, m_owner.m_Actor);
		m_owner.Send(rsp);
	}
	{
		SetWarMode rsp(false);
		m_owner.Send(rsp);
	}
	{
		SeasonChange rsp;
		m_owner.Send(rsp);
	}
	{
		CurrentTime rsp;
		m_owner.Send(rsp);
	}
	{
		MapChange rsp(m_owner.m_Actor);
		m_owner.Send(rsp);
	}

	//m.SendEverything();
	L_DEBUG("Entered World");
}

void LoginPlayer::ClientDisCon()
{
	L_COND_V(LoginOk == m_State);
	m_State = OffLine;
}

RegCenterMsg(LoginPlayer::ReqLoginZone_sc);
void LoginPlayer::ReqLoginZone_sc(CenterCon &con, const proto::ReqLoginZone_sc &msg)
{
	std::unique_ptr<BaseTable> baseTable = TableCfg::Ins().Unpack(msg.playerData);
	DbPlayer * playerData = dynamic_cast<DbPlayer *>(baseTable.get());
	L_COND_V(playerData);
	L_INFO("player %s login zone.", playerData->name.c_str());

	Player *player = PlayerMgr::Ins().Create(playerData->uin, playerData->name);
	L_COND_V(player);

	{//init session
		const Session *sn = AccMgr::Ins().FindSessionByCid(msg.cid);
		ZoneSnEx *pZoneSnEx = sn->GetEx<ZoneSnEx>();
		L_COND_V(pZoneSnEx);
		pZoneSnEx->m_pPlayer = *player;

		acc::SessionId sid;
		sid.cid = msg.cid;
		player->m_PlayerSn.SetSid(sid);
		player->m_PlayerSn.m_ns.Init(*sn);
	}

	RspLoginZone_cs rsp;
	rsp.uin = playerData->uin;
	rsp.ret = true;
	con.Send(rsp);

	if (msg.isCreate)
	{
		player->m_PlayerDb.OnCreate(*playerData);
	}
	else
	{
		player->m_PlayerDb.OnLoad(*playerData);
	}
	player->m_LoginPlayer.Login();
}

RegCenterMsg(LoginPlayer::ReqReLoginZone_sc);
void LoginPlayer::ReqReLoginZone_sc(CenterCon &con, const proto::ReqReLoginZone_sc &msg)
{
	L_INFO("ReqReLoginZone_sc");
	Player *player = PlayerMgr::Ins().Find(msg.uin);
	L_COND_V(player);

	L_COND_V(LoginOk == player->m_LoginPlayer.m_State || OffLine == player->m_LoginPlayer.m_State);
	const Session *sn = AccMgr::Ins().FindSessionByCid(msg.cid);
	ZoneSnEx *pZoneSnEx = sn->GetEx<ZoneSnEx>();
	L_COND_V(pZoneSnEx);
	pZoneSnEx->m_pPlayer = *player;
	player->m_LoginPlayer.m_State = LoginOk;

	RspReLoginZone_cs rsp;
	rsp.ret = true;
	CenterCon::Ins().Send(rsp);
}
