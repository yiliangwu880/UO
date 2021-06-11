#include "SceneMgr.h"
#include "AppMgr.h"



GRegEvent(EV_SVR_START, SceneMgr::Start);
void SceneMgr::Start(bool &ret)
{
	SceneMgr::Ins().InitWorld(MapId::Felucca);
	SceneMgr::Ins().InitWorld(MapId::Trammel);
	SceneMgr::Ins().InitWorld(MapId::Ilshenar);
	SceneMgr::Ins().InitWorld(MapId::Malas);
	SceneMgr::Ins().InitWorld(MapId::Tokuno);
	SceneMgr::Ins().InitWorld(MapId::TerMur);
	SceneMgr::Ins().InitWorld(MapId::Internal);

	FireEvent<EV_FINISH_WORLD_SCENE>();
}

void SceneMgr::InitWorld(MapId mapId)
{
	SceneId sceneId;
	sceneId.fbId = 0;
	sceneId.mapId = (uint16)MapId::Felucca;
	shared_ptr<Scene> p = make_shared<Scene>(sceneId);
	SceneMgr::Ins().m_all.insert(make_pair(sceneId.id, p));
}

Scene &SceneMgr::GetWorld(MapId mapId)
{
	SceneId id((uint16)mapId, 0);
	Scene *p =  Find(id.id);
	if (nullptr == p)
	{
		L_FATAL("can't find world");
	}
	return *p;
}

Scene * SceneMgr::CreateFb(uint16 mapId)
{
	static uint16 fbSeed = 0;//基本够用，低概率重复
	if (fbSeed == 0)
	{
		fbSeed++;
	}
	SceneId sceneId;
	sceneId.fbId = fbSeed++;
	sceneId.mapId = mapId;
	shared_ptr<Scene> p = make_shared<Scene>(sceneId);
	bool r = m_all.insert(make_pair(sceneId.id, p)).second;
	if (!r)
	{
		L_ERROR("create fail");
		return nullptr;
	}
	return p.get();
}

Scene * SceneMgr::Find(uint32 sceneId)
{
	shared_ptr<Scene> *pp = MapFind(m_all, sceneId);
	L_COND(pp, nullptr);
	return (*pp).get();
}

void SceneMgr::Del(uint32 sceneId)
{
	auto f = [this, sceneId]()
	{
		shared_ptr<Scene> *pp = MapFind(m_all, sceneId);
		L_COND_V(pp, "del fail");
		if (!m_all.erase(sceneId))
		{
			L_ERROR("del fail");
		}
	};
	AppMgr::Ins().AddPost(f);
}

