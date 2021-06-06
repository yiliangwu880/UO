#pragma once
#include "InsEvent.h"

#define PINFO(player, x, ...) \
{\
	char str[1000];\
	snprintf(str, sizeof(str), "[%d %s] %s", m_owner.Uin(), m_owner.Name().c_str(), x);\
	L_INFO(str, ##__VA_ARGS__);\
}\



class Player;
template<class SubComClass>
class PlayerSubCom : public EventCom<SubComClass>
{
public:
	Player &m_owner;
public:
	PlayerSubCom(Player &owner)
		:EventCom<SubComClass>(owner)
		, m_owner(owner)
	{
	}
};
