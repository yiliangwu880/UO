#include "PlayerMgr.h"

Player * PlayerMgr::CreatePlayer(uint64 uin, const string &name)
{
	return m_players.emplace(uin, name, Player());
}
Player * PlayerMgr::FindPlayer(uint64 uin)
{
	return m_players.Find(uin);
}

Player * PlayerMgr::FindPlayer(const string &name)
{
	return m_players.SubFind(name);
}

void PlayerMgr::DelPlayer(uint64 uin)
{
	auto f = [this, uin]()
	{
		if (!m_players.erase(uin))
		{
			L_ERROR("del fail");
		}
	};
	AppMgr::Ins().AddPost(f);
}

void PlayerMgr::SetCacheMsg(uint64 uin, bool isCache)
{

}
