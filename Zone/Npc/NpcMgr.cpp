#include "NpcMgr.h"
#include "AppMgr.h"

using PMonster = Npc * ;
Npc * NpcMgr::Create()
{
	static uint32 uinSeed = 1;//够用了
	uint32 uin = uinSeed++;
	Npc *p = new Npc(uin);
	bool r = m_all.insert(make_pair(uin, p)).second;
	if (!r)
	{
		L_ERROR("create fail");
		delete p;
		return nullptr;
	}
	return p;
}

Npc * NpcMgr::Find(uint32 uin)
{
	PMonster *pp = MapFind(m_all, uin);
	L_COND(pp, nullptr);
	return *pp;
}

void NpcMgr::Del(uint32 uin)
{
	auto f = [this, uin]()
	{
		PMonster *pp = MapFind(m_all, uin);
		L_COND_V(pp, "del fail");
		delete *pp;
		if (!m_all.erase(uin))
		{
			L_ERROR("del fail");
		}
	};
	AppMgr::Ins().AddPost(f);
}
