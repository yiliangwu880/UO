
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
class PlayerMgr : Singleton<PlayerMgr>
{
	MulMapPlayer m_players;

	vector<PlayerCacheMsg> m_PlayerCacheMsg; //player Moving״̬���������Ϣ����Ϊuin�������١���vector��mapЧ�ʸߡ�
public:
	Player *CreatePlayer(uint64 uin, const string &name);
	Player *GetPlayer(uint64 uin);
	void SetCacheMsg(uint64 uin, bool isCache);
private:

};


