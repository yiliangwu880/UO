#include "PlayerMgr.h"
#include "AppMgr.h"

Player * PlayerMgr::CreatePlayer(uint64 uin, CStr &name)
{
	Player *p = new Player(uin, name);
	if (!m_players.Insert(p))
	{
		delete p;
		return nullptr;
	}
	return p;
}

Player * PlayerMgr::FindPlayer(uint64 uin)
{
	PPlayer *pp = m_players.Find(uin);
	L_COND(pp, nullptr);
	return *pp;
}

Player * PlayerMgr::FindPlayer(const string &name)
{
	PPlayer *pp = m_players.SubFind(name);
	L_COND(pp, nullptr);
	return *pp;
}

void PlayerMgr::DelPlayer(uint64 uin)
{
	auto f = [this, uin]()
	{
		PPlayer *pp = m_players.Find(uin);
		L_COND_V(pp, "del fail");
		delete *pp;
		if (!m_players.erase(uin))
		{
			L_ERROR("del fail");
		}
	};
	AppMgr::Ins().AddPost(f);
}




