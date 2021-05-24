#include "PlayerMgr.h"

Player * PlayerMgr::CreatePlayer(uint64 uin)
{
	return nullptr;
}
Player * PlayerMgr::FindPlayer(uint64 uin)
{
	return nullptr;
}

void PlayerMgr::DelPlayer(uint64 uin)
{
	auto f = [this]()
	{
		auto it = m_players.find(name);
		if (it == m_players.end())
		{
			L_ERROR("del fail");
			return;
		}
		m_players.erase(it);
	};
	AppMgr::Ins().AddPost(f);
}




