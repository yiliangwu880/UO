#include "SceneMgr.h"
#include "AppMgr.h"

using PScene = Scene *;

Scene SceneMgr::Felucca;

GRegEvent(EV_SVR_START, SceneMgr::Start);
void SceneMgr::Start(bool &ret)
{
	SceneMgr::Felucca.Init();



	FireEvent<EV_FINISH_WORLD_SCENE>();
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

