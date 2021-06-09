#include "Npc.h"
#include "AppMgr.h"

void Npc::PostDel()
{
	delete this;
}

Npc::Npc(uint32 id)
	:m_actor(*this)
	,m_ai(*this, m_actor)
{
	m_id = id;
}

bool Npc::Enter(Scene &scene, uint16 x, uint16 y)
{
	return m_actor.m_Observer.Enter(scene.m_aoi, x, y);
}
