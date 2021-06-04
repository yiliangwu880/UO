#pragma once
#include "ComMisc.h"


#define PINFO(player, x, ...) \
{\
	char str[1000];\
	snprintf(str, sizeof(str), "[%d %s] %s", m_owner.Uin(), m_owner.Name().c_str(), x);\
	L_INFO(str, ##__VA_ARGS__);\
}\


using PlayerSubCom = SubCom<Player>;
struct BaseData : public PlayerSubCom
{
	uint64 m_uin = 0;
	string name;

	BaseData(Player &owner)
		:PlayerSubCom(owner)
	{}
};

