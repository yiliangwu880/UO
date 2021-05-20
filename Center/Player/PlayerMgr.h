
#pragma once
#include "Player.h"

class PlayerMgr : Singleton<PlayerMgr>
{
	std::unordered_map<uint64, Player> m_players;
public:
	bool CreatePlayer(uint64 uin);

private:

};


