#include "PlayerMgr.h"

Player * PlayerMgr::CreatePlayer(uint64 uin, const string &name)
{
	return m_players.emplace(uin, name, Player());
}
Player * PlayerMgr::GetPlayer(uint64 uin)
{
	return m_players.Find(uin);
}

void PlayerMgr::SetCacheMsg(uint64 uin, bool isCache)
{

}
