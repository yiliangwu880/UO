#include "NpcMgr.h"
#include "AppMgr.h"

using PMonster = Npc * ;
Npc * NpcMgr::Create()
{
	static uint32 uinSeed = 1;//够用了
	uint32 uin = uinSeed++;
	shared_ptr<Npc> p = make_shared<Npc>(uin);
	bool r = m_all.insert(make_pair(uin, p)).second;
	if (!r)
	{
		L_ERROR("create fail");
		return nullptr;
	}
	return p.get();
}

Npc * NpcMgr::Find(uint32 uin)
{
	shared_ptr<Npc> *pp = MapFind(m_all, uin);
	L_COND(pp, nullptr);
	return pp->get();
}

void NpcMgr::Del(uint32 uin)
{
	auto f = [this, uin]()
	{
		shared_ptr<Npc> *pp = MapFind(m_all, uin);
		L_COND_V(pp, "del fail");
		(*pp)->m_Actor.m_Observer.Leave();
		if (!m_all.erase(uin))
		{
			L_ERROR("del fail");
		}
	};
	AppMgr::Ins().AddPost(f);
}
