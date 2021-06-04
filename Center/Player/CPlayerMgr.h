
#pragma once
#include "CPlayer.h"
#include "MulMap.h"
#include "CPlayer.h"

using PCPlayer = CPlayer *;
template<>
struct MulMapTraits<PCPlayer>
{
	friend struct CPlayer;
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
class CPlayerMgr : public Singleton<CPlayerMgr>
{
	MulMapPlayer m_players;

	vector<PlayerCacheMsg> m_PlayerCacheMsg; //player Moving状态，缓存的消息。因为uin数量极少。用vector比map效率高。

public:
	CPlayer *CreatePlayer(const DbPlayer &data);
	CPlayer *FindPlayer(uint64 uin);
	CPlayer *FindPlayer(const string &name);
	void DelPlayer(uint64 uin);
	void SetCacheMsg(uint64 uin, bool isCache);

private:

};


