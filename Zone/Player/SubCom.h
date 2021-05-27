#pragma once


#define PINFO(player, x, ...) \
{\
	char str[1000];\
	snprintf(str, sizeof(str), "[%d %s] %s", m_owner.Uin(), m_owner.Name().c_str(), x);\
	L_INFO(str, ##__VA_ARGS__);\
}\

class Player;
class SubCom
{
public:
	Player &m_owner;
	SubCom();
};

