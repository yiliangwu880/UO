#include "MonsterMgr.h"
#include "AppMgr.h"
#include "SceneMgr.h"

using PMonster = Monster * ;

GRegEvent(EV_FINISH_WORLD_SCENE, MonsterMgr::OnFinishWorld)
void MonsterMgr::OnFinishWorld()
{
	Monster *m = MonsterMgr::Ins().Create();
	{//tmp create a monster
		const MonsterCfg *pCfg = gCfg.GetMonsterCfg(1);
		L_COND_V(pCfg);

		MonsterInit d;
		d.cfg = pCfg;
		d.scene = &SceneMgr::Felucca;
		d.pos = gCfg.GetMiscCfg().bornPos;
		m->Init(d);
	}
}

Monster * MonsterMgr::Create()
{
	static uint32 uinSeed = 1;//够用了
	uint32 uin = uinSeed++;
	Monster *p = new Monster(uin);
	bool r = m_all.insert(make_pair(uin, p)).second;
	if (!r)
	{
		L_ERROR("create fail");
		delete p;
		return nullptr;
	}
	return p;
}

Monster * MonsterMgr::Find(uint32 uin)
{
	PMonster *pp = MapFind(m_all, uin);
	L_COND(pp, nullptr);
	return *pp;
}

void MonsterMgr::Del(uint32 uin)
{
	auto f = [this, uin]()
	{
		PMonster *pp = MapFind(m_all, uin);
		L_COND_V(pp, "del fail");
		(*pp)->m_Actor.m_Observer.Leave();
		delete *pp;
		if (!m_all.erase(uin))
		{
			L_ERROR("del fail");
		}
	};
	AppMgr::Ins().AddPost(f);
}
