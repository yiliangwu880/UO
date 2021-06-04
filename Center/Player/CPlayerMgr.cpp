#include "CPlayerMgr.h"
#include "AppMgr.h"

CPlayer * CPlayerMgr::CreatePlayer(uint64 uin, const string &name)
{
	CPlayer *p = new CPlayer();
	PCPlayer *pp = m_players.emplace(uin, name, p);
	L_COND(pp, nullptr);
	return *pp;
}

CPlayer * CPlayerMgr::FindPlayer(uint64 uin)
{
	PCPlayer *pp = m_players.Find(uin);
	L_COND(pp, nullptr);
	return *pp;
}

CPlayer * CPlayerMgr::FindPlayer(const string &name)
{
	PCPlayer *pp = m_players.SubFind(name);
	L_COND(pp, nullptr);
	return *pp;
}

void CPlayerMgr::DelPlayer(uint64 uin)
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

void CPlayerMgr::SetCacheMsg(uint64 uin, bool isCache)
{

}
