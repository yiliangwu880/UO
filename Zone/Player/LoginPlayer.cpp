#include "PlayerMgr.h"

using namespace proto;
using namespace acc;

void LoginPlayer::Login()
{
	Scene &scene = SceneMgr::Ins().GetWorld(MapId::Felucca);
	m_owner.m_Actor.EnterScene(scene);
	m_owner.FireEvent<EV_BEFORE_LOGIN>(); 
	SendLogin();
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
		m_owner.SendHexStr( 0, "BF 0 0 0 18 0 0 0 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
		//state.Send(SupportedFeatures.Instantiate(state));
		m_owner.SendHexStr(1, "B9 0 FF 92 DB");
	}
	{
		MobileIncoming rsp(m_owner.m_Actor, m_owner.m_Actor);
		m_owner.Send(rsp);
	}
	//m.SendEverything();

	//m.CheckLightLevels(true);
	{
		GlobalLightLevel rsp(12);
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

	acc::SessionId sid;
	sid.cid = msg.cid;
	player->m_PlayerSn.SetSid(sid);

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
	WeakPlayer *weakPlayer = sn->GetEx<WeakPlayer>();
	L_COND_V(weakPlayer);
	*weakPlayer = *player;
	player->m_LoginPlayer.m_State = LoginOk;

	RspReLoginZone_cs rsp;
	rsp.ret = true;
	CenterCon::Ins().Send(rsp);
}
