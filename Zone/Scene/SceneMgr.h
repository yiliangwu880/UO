#pragma once
#include "Scene.h"

class SceneMgr : public Singleton<SceneMgr>
{
private:
	unordered_map<uint32, shared_ptr<Scene>> m_all;

public:
	static Scene Felucca;
	//static Scene Trammel;//Trammel新世界,安全，资源少
	//static Scene Ilshenar;
	//static Scene Malas;
	//static Scene Tokuno;
	//static Scene TerMur;
	//static Scene Internal;
public:
	static void Start(bool &ret );


public:
	Scene *CreateFb(uint16 mapId);
	Scene *Find(uint32 sceneId);
	void Del(uint32 sceneId);


};