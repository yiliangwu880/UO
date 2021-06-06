#pragma once
#include "InsEvent.h"

class Actor;
class ActorEquip : public EventCom<ActorEquip>
{
	Actor &m_owner;
public:
	ActorEquip(Actor &owner);

};