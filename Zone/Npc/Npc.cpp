#include "Npc.h"

void Npc::PostDel()
{
	delete this;
}

Npc::Npc()
	:m_actor(*this)
{

}
