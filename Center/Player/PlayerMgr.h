
#pragma once
#include "Player.h"
#include "MulMap.h"

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

struct PlayerCacheMsg
{
	uint64 uin;
	VecStr vecMsg;
};
class PlayerMgr : public Singleton<PlayerMgr>
{
	MulMapPlayer m_players;

	vector<PlayerCacheMsg> m_PlayerCacheMsg; //player Moving状态，缓存的消息。因为uin数量极少。用vector比map效率高。

public:
	Player *CreatePlayer(uint64 uin, const string &name);
	Player *FindPlayer(uint64 uin);
	Player *FindPlayer(const string &name);
	void DelPlayer(uint64 uin);
	void SetCacheMsg(uint64 uin, bool isCache);

private:

};


