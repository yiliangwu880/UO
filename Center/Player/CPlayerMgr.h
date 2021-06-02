
#pragma once
#include "CPlayer.h"
#include "MulMap.h"

template<>
struct MulMapTraits<CPlayer>
{
	friend struct CPlayer;
	static string GetSubKey(const CPlayer &player)
	{
		return player.m_BaseData.name;
	}
	static void SetKey(CPlayer &player, uint64 mainKey, string subKey)
	{
		player.m_BaseData.m_uin = mainKey;
		player.m_BaseData.name = subKey;
	}
};
using MulMapPlayer = MulMap<uint64, string, CPlayer>;

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
	CPlayer *CreatePlayer(uint64 uin, const string &name);
	CPlayer *FindPlayer(uint64 uin);
	CPlayer *FindPlayer(const string &name);
	void DelPlayer(uint64 uin);
	void SetCacheMsg(uint64 uin, bool isCache);

private:

};


