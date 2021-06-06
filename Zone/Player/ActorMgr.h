#pragma once
#include "SubCom.h"


class ActorMgr : public PlayerSubCom<ActorMgr>
{
public:
	ActorMgr(Player &owner);
	void OnLoad(DbPlayer &data);
};

