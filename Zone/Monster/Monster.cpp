#include "Monster.h"

void Monster::PostDel()
{
	delete this;
}

Monster::Monster()
	:m_actor(*this)
{
	
}
