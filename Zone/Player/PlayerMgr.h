
#pragma once
#include "Player.h"
#include "MulMap.h"


using PPlayer = Player *;
template<>
struct MulMapTraits<PPlayer>
{
	friend struct Player;
	static uint64 GetKey(const PPlayer &player)
	{
		return player->m_BaseData.m_uin;
	}
	static string GetSubKey(const PPlayer &player)
	{
		return player->m_BaseData.name;
	}

};
using MulMapPlayer = MulMap<uint64, string, PPlayer>;


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


