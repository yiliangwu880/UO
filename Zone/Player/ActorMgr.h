#pragma once
#include "SubCom.h"
#include "Actor/Actor.h"

class ActorMgr : public PlayerSubCom<ActorMgr>
{
	//Actor m_actor;

public:
	ActorMgr(Player &owner);
	void OnLoad(DbPlayer &data);
};

