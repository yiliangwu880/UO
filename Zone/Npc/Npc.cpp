#include "Npc.h"

void Npc::PostDel()
{
	delete this;
}

Npc::Npc()
	:m_actor(*this)
	,m_ai(*this, m_actor)
{

}
