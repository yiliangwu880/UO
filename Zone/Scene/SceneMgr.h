#pragma once
#include "Scene.h"

class SceneMgr : public Singleton<SceneMgr>
{
private:
	unordered_map<uint32, shared_ptr<Scene>> m_all;

public:
	static void Start(bool &ret );


public:
	Scene &GetWorld(MapId mapId);
	Scene *CreateFb(uint16 mapId);
	Scene *Find(uint32 sceneId);
	void Del(uint32 sceneId);

private:
	void InitWorld(MapId mapId);
};