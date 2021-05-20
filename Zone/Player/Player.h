#pragma once
#include "dbTableDef.h"
#include "AccMgr.h"
#include "MsgDispatch.h"

class SceneTran
{
	enum class State
	{
		Playing,
		Moving,
	};
	State m_State;

public:
	State GetState() const { return m_State; }
	void SetState(State val);
};

struct BaseData 
{
	uint64 m_uin = 0;
	acc::SessionId sid;
};

class Player
{
	BaseData m_BaseData;
	SceneTran m_SceneTran;

public:
	void Init(uint64 uin) {};
	bool Load(db::Player &data);

	template<class Msg>
	void Send(const Msg &msg)
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

