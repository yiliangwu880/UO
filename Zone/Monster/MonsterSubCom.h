#pragma once
#include "InsEvent.h"


class Monster;
template<class SubComClass>
class MonsterSubCom : public EventCom<SubComClass>
{
public:
	Monster &m_owner;
public:
	MonsterSubCom(Monster &owner)
		:EventCom<SubComClass>(owner)
		, m_owner(owner)
	{
	}
};
