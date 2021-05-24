
#pragma once
#include "Player.h"


template<>
struct MulMapTraits<Player>
{
	friend struct Player;
	static string GetSubKey(const Player &player)
	{
		return player.m_BaseData.name;
	}
	static void SetKey(Player &player, uint64 mainKey, string subKey)
	{
		player.m_BaseData.m_uin = mainKey;
		player.m_BaseData.name = subKey;
	}
};
using MulMapPlayer = MulMap<uint64, string, Player>;


class PlayerMgr : Singleton<PlayerMgr>
{
	MulMapPlayer m_players;

public:
	Player *CreatePlayer(uint64 uin, const string &name);
	Player *FindPlayer(uint64 uin);
	Player *FindPlayer(const string &name);
	void DelPlayer(uint64 uin);
public:

private:

};


