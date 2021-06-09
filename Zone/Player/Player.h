#pragma once
#include "dbTableDef.h"
#include "AccMgr.h"
#include "MsgDispatch.h"
#include "LoginPlayer.h"
#include "SceneTran.h"
#include "PlayerSn.h"
#include "PlayerDb.h"
#include "Actor/Actor.h"
#include "SceneMgr.h"


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


	//send to client, wait modify or del
	template<class ProtoMsg>
	void Send(const ProtoMsg &msg)
	{
		lc::MsgPack msgPack;
		size_t len = sizeof(msgPack.data);
		char *p = msgPack.data;
		L_ASSERT(proto::Pack(msg, p, len));
		msgPack.len = sizeof(msgPack.data) - len;
		//todo cmd 合并一起
		AccMgr::Ins().SendToClient(m_PlayerSn.GetSid(), 0, msgPack.data, msgPack.len);
	}

	uint64 Uin() { return m_BaseData.m_uin; }
	string &Name() { return m_BaseData.name; }

private:

};

