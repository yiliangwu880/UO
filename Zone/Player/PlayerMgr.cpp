#include "PlayerMgr.h"
#include "AppMgr.h"

Player * PlayerMgr::Create(uint64 uin, CStr &name)
{
	shared_ptr<Player> p = make_shared<Player>(uin, name);
	if (!m_all.Insert(p))
	{
		L_ERROR("create fail");
		return nullptr;
	}
	return p.get();
}

Player * PlayerMgr::Find(uint64 uin)
{
	shared_ptr<Player> *pp = m_all.Find(uin);
	L_COND(pp, nullptr);
	return pp->get();
}

Player * PlayerMgr::Find(const string &name)
{
	shared_ptr<Player> *pp = m_all.SubFind(name);
	L_COND(pp, nullptr);
	return pp->get();
}

void PlayerMgr::Del(uint64 uin)
{
	auto f = [this, uin]()
	{
		shared_ptr<Player> *pp = m_all.Find(uin);
		L_COND_V(pp, "del fail");
		(*pp)->m_Actor.m_Observer.Leave();
		if (!m_all.erase(uin))
		{
			L_ERROR("del fail");
		}
	};
	AppMgr::Ins().AddPost(f);
}




