#include "CPlayerMgr.h"
#include "AppMgr.h"

CPlayer * CPlayerMgr::CreatePlayer(uint64 uin, const string &name)
{
	return m_players.emplace(uin, name, CPlayer());
}
CPlayer * CPlayerMgr::FindPlayer(uint64 uin)
{
	return m_players.Find(uin);
}

CPlayer * CPlayerMgr::FindPlayer(const string &name)
{
	return m_players.SubFind(name);
}

void CPlayerMgr::DelPlayer(uint64 uin)
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

void CPlayerMgr::SetCacheMsg(uint64 uin, bool isCache)
{

}
