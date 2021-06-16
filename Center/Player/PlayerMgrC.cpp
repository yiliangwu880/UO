#include "PlayerMgrC.h"
#include "AppMgr.h"

PlayerC * PlayerMgrC::CreatePlayer(const DbPlayer &data)
{
	PlayerC *p = new PlayerC(data);
	if (!m_players.Insert(p))
	{
		delete p;
		return nullptr;
	}
	return p;
}

PlayerC * PlayerMgrC::FindPlayer(uint64 uin)
{
	PCPlayer *pp = m_players.Find(uin);
	L_COND(pp, nullptr, "uin=%ld", uin);
	return *pp;
}

PlayerC * PlayerMgrC::FindPlayer(const string &name)
{
	PCPlayer *pp = m_players.SubFind(name);
	L_COND(pp, nullptr);
	return *pp;
}

void PlayerMgrC::DelPlayer(uint64 uin)
{
	auto f = [this, uin]()
	{	
		PCPlayer *pp = m_players.Find(uin);
		L_COND_V(pp, "del fail");
		delete *pp;
		if (!m_players.erase(uin))
		{
			L_ERROR("del fail");
		}
	};
	AppMgr::Ins().AddPost(f);
}

void PlayerMgrC::SetCacheMsg(uint64 uin, bool isCache)
{

}
