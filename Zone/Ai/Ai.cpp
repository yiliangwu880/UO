#include "Ai.h"

Ai::Ai(ActorOwner &owner, Actor &actor)
	:EventCom<Ai>(owner)
	, m_owner(owner)
	, m_Actor(actor)
	, m_ActStateMgr(owner, actor)
{

}
