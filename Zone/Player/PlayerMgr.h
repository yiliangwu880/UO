
#pragma once
#include "Player.h"

class PlayerMgr : Singleton<PlayerMgr>
{
	std::unordered_map<uint64, Player> m_players;

public:
	Player *CreatePlayer(uint64 uin);
	Player *FindPlayer(uint64 uin);
	void DelPlayer(uint64 uin);
public:

private:

};


