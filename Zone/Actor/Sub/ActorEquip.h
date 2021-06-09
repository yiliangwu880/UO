#pragma once
#include "ActorSubCom.h"

class ActorEquip : public ActorSubCom<ActorEquip>
{
	DbEquips *m_equips = nullptr;
public:
	ActorEquip(Actor &actor);
	void OnLoad(DbPlayer &dbActor);
};