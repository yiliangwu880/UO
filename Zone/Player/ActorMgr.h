#pragma once
#include "BaseData.h"


class ActorMgr : public PlayerSubCom, public EventCom<ActorMgr>
{
public:
	ActorMgr(Player &owner);
	void OnLoad(DbPlayer &data);
};

