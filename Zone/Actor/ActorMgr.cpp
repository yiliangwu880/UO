#include "ActorMgr.h"

void ActorMgr::AddActor(Actor &actor)
{
	WActor p = actor;
	bool r = MapInsert(m_id2Actor, actor.m_ActorBase.GetId(), p);
	L_COND_V(r);
	L_DEBUG("add actor %d", actor.m_ActorBase.GetId());
}

void ActorMgr::DelActor(uint32 id)
{
	L_COND_V(MapErase(m_id2Actor, id));
	L_DEBUG("del actor %d", id);
}

Actor * ActorMgr::Find(uint32 id)
{
	WActor *pp = MapFind(m_id2Actor, id);
	SActor p = pp->lock();
	return p.get();
}
