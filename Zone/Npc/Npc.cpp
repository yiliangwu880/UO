#include "Npc.h"
#include "AppMgr.h"



Npc::Npc(uint32 id)
	:ActorOwner(m_DbActor)
	,m_Actor(*this)
	,m_ai(*this, m_Actor)
{
	m_id = id;
}

