
#pragma once
#include "PlayerC.h"
#include "MulMap.h"
#include "PlayerC.h"

using PCPlayer = PlayerC *;
template<>
struct MulMapTraits<PCPlayer>
{
	friend struct PlayerC;
	static uint64 GetKey(const PCPlayer &player)
	{
		return player->m_BaseData.m_uin;
	}
	static string GetSubKey(const PCPlayer &player)
	{
		return player->m_BaseData.name;
	}
	static void SetKey(PCPlayer &player, uint64 mainKey, string subKey)
	{
		player->m_BaseData.m_uin = mainKey;
		player->m_BaseData.name = subKey;
	}
};
using MulMapPlayer = MulMap<uint64, string, PCPlayer>;

struct PlayerCacheMsg
{
	uint64 uin;
	VecStr vecMsg;
};
class PlayerMgrC : public Singleton<PlayerMgrC>
{
	MulMapPlayer m_players;

	vector<PlayerCacheMsg> m_PlayerCacheMsg; //player Moving状态，缓存的消息。因为uin数量极少。用vector比map效率高。

public:
	PlayerC *CreatePlayer(const DbPlayer &data);
	PlayerC *FindPlayer(uint64 uin);
	PlayerC *FindPlayer(const string &name);
	void DelPlayer(uint64 uin);
	void SetCacheMsg(uint64 uin, bool isCache);

private:

};


