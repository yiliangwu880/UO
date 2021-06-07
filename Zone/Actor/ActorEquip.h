#pragma once
#include "InsEvent.h"

class Actor;
class ActorEquip : public EventCom<ActorEquip>
{
	Actor &m_owner;
	DbEquips *m_equips = nullptr;
public:
	ActorEquip(Actor &owner);
	void OnLoad(DbPlayer &dbActor);
};