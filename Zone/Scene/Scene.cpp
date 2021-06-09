#include "Scene.h"

Scene::Scene(SceneId sceneId)
	:m_SceneId(sceneId)
{

}

void Scene::Init()
{
}

void Scene::Init(uint16 mapId)
{
	m_SceneId.mapId = mapId;
}
