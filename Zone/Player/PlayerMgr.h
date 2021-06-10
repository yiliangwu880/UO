
#pragma once
#include "Player.h"
#include "MulMap.h"


template<>
struct MulMapTraits<shared_ptr<Player>>
{
	friend struct Player;
	static uint64 GetKey(const shared_ptr<Player> &player)
	{
		return player->m_BaseData.m_uin;
	}
	static string GetSubKey(const shared_ptr<Player> &player)
	{
		return player->m_BaseData.name;
	}

};
using MulMapPlayer = MulMap<uint64, string, shared_ptr<Player>>; //安全优先，效率先不考虑。不用new


class PlayerMgr : public Singleton<PlayerMgr>
{
	MulMapPlayer m_all;

public:
	Player *Create(uint64 uin, const string &name);
	Player *Find(uint64 uin);
	Player *Find(const string &name);
	void Del(uint64 uin);
public:

private:

};


