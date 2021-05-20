#include "PlayerMgr.h"

bool PlayerMgr::CreatePlayer(uint64 uin)
{
	if (Player *player = MapFind(m_players, uin))
	{
		return false;
	}
	map<int, Player> m;
	MapInsert(m_players, uin, Player());
	return true;
}
