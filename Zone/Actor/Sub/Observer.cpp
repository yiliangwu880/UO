#include "Actor.h"

void Observer::OnAddObserver(Entity &other)
{

}

void Observer::OnDelObserver(Entity &other)
{

}

Observer::Observer(Actor &actor, EntityType type)
	:ActorSubCom<Observer>(actor.m_owner, actor)
	, Aoi::Entity(type)
{

}

bool Observer::Enter(Scene &scene, uint16_t x, uint16_t y)
{
	bool r = Aoi::Entity::Enter(scene.m_aoi, x, y);
	if (r)
	{
		m_Actor.m_ActorBase.SetSceneId(scene.GetId());
	}
	return r;
}

bool Observer::Leave()
{
	m_Actor.m_ActorBase.SetSceneId(0);
	return Aoi::Entity::Leave();
}
