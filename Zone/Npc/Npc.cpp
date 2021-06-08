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
