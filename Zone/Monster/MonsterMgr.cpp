#include "MonsterMgr.h"
#include "AppMgr.h"
#include "SceneMgr.h"


GRegEvent(EV_FINISH_WORLD_SCENE, MonsterMgr::OnFinishWorld)
void MonsterMgr::OnFinishWorld()
{
	Monster *m = MonsterMgr::Ins().Create();
	{//tmp create a monster
		const MonsterCfg *pCfg = gCfg.GetMonsterCfg(1);
		L_COND_V(pCfg);

		MonsterInit d;
		d.cfg = pCfg;
		d.scene = SceneMgr::Ins().GetWorld(MapId::Felucca);
		L_COND_V(d.scene);
		d.pos = gComCfg.GetMiscCfg().bornPos;
		m->Init(d);
	}
#if 0
	{
		//load from db.for player's pet;
		//	DbActor data;

		//Monster *m = MonsterMgr::Ins().Create();
		//event load db;
		//m.init();
	}
#endif
}

Monster * MonsterMgr::Create()
{
	static uint32 uinSeed = 1;//够用了
	uint32 uin = uinSeed++;
	shared_ptr<Monster> p = make_shared<Monster>(uin);
	bool r = m_all.insert(make_pair(uin, p)).second;
	if (!r)
	{
		L_ERROR("create fail");
		return nullptr;
	}
	return p.get();
}

Monster * MonsterMgr::Find(uint32 uin)
{
	shared_ptr<Monster> *pp = MapFind(m_all, uin);
	L_COND(pp, nullptr);
	return pp->get();
}

void MonsterMgr::Del(uint32 uin)
{
	auto f = [this, uin]()
	{
		auto *pp = MapFind(m_all, uin);
		L_COND_V(pp, "del fail");
		(*pp)->m_Actor.m_Observer.Leave();
		if (!m_all.erase(uin))
		{
			L_ERROR("del fail");
		}
	};
	AppMgr::Ins().AddPost(f);
}
