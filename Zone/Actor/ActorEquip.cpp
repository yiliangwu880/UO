#include "Actor.h"

ActorEquip::ActorEquip(Actor &owner)
	:EventCom<ActorEquip>(owner.m_owner)
	,m_owner(owner)
{

}
