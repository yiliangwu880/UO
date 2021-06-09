#pragma once
#include "InsEvent.h"


class Npc;
template<class SubComClass>
class NpcSubCom : public EventCom<SubComClass>
{
public:
	Npc &m_owner;
public:
	NpcSubCom(Npc &owner)
		:EventCom<SubComClass>(owner)
		, m_owner(owner)
	{
	}
};
