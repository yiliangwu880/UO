#include "PlayerMgr.h"
#include "AppMgr.h"

Player * PlayerMgr::Create(uint64 uin, CStr &name)
{
	Player *p = new Player(uin, name);
	if (!m_all.Insert(p))
	{
		L_ERROR("create fail");
		delete p;
		return nullptr;
	}
	return p;
}

Player * PlayerMgr::Find(uint64 uin)
{
	PPlayer *pp = m_all.Find(uin);
	L_COND(pp, nullptr);
	return *pp;
}

Player * PlayerMgr::Find(const string &name)
{
	PPlayer *pp = m_all.SubFind(name);
	L_COND(pp, nullptr);
	return *pp;
}

void PlayerMgr::Del(uint64 uin)
{
	auto f = [this, uin]()
	{
		PPlayer *pp = m_all.Find(uin);
		L_COND_V(pp, "del fail");
		delete *pp;
		if (!m_all.erase(uin))
		{
			L_ERROR("del fail");
		}
	};
	AppMgr::Ins().AddPost(f);
}




