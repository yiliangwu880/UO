#pragma once
#include "Scene.h"

class SceneMgr : public Singleton<SceneMgr>
{
	unordered_map<uint16, Scene *> m_alls;
	Scene m_tmp;
public:
	Scene *FindScene(uint32 sceneId);
};