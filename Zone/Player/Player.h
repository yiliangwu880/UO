#pragma once
#include "dbTableDef.h"
#include "AccMgr.h"
#include "MsgDispatch.h"

class PlayerSubCom
{
public:
	Player m_owner;
};

struct BaseData 
{
	uint64 m_uin = 0;
	acc::SessionId sid;
};

class Player
{
	BaseData m_BaseData;
	PlayerScene m_SceneTran;

public:
	void Init(uint64 uin) {};
	bool Load(db::Player &data);

	template<class ProtoMsg>
	void Send(const ProtoMsg &msg)
	{
		lc::MsgPack msgPack;
		size_t len = sizeof(msgPack.data);
		char *p = msgPack.data;
		L_ASSERT(proto::Pack(msg, p, len));
		//todo cmd 合并一起
		AccMgr::Ins().SendToClient(m_BaseData.sid, 0, msgPack.data, msgPack.len);
	}

private:

};

