#include "Monster.h"

void Monster::PostDel()
{
	delete this;
}

Monster::Monster()
	:m_actor(*this)
	, m_ai(*this, m_actor)
{
	
}
