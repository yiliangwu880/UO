#pragma once
#include "dbTableDef.h"
#include "ZoneAccMgr.h"
#include "MsgDispatch.h"
#include "LoginPlayer.h"
#include "SceneTran.h"
#include "PlayerSn.h"
#include "PlayerDb.h"
#include "Actor/Actor.h"
#include "SceneMgr.h"
#include "Packets.h"


class Player : public WeakPtr<Player>, public ActorOwner
{

public:
	PlayerDb	m_PlayerDb; //必须放前面，下面组件才能正确引用
	BaseData    m_BaseData;
	PlayerSn    m_PlayerSn;
	SceneTran   m_SceneTran;
	LoginPlayer m_LoginPlayer;
	Actor		m_Actor;

public:
	Player(uint64 uin, CStr &name);


	void Send(Packet &msg){m_PlayerSn.Send(msg);}
	void SendHexStr(bool isFixed, const char *p);

	uint64 Uin() { return m_BaseData.m_uin; }
	string &Name() { return m_BaseData.name; }

private:

};

