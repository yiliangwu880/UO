#include "Ai.h"

Ai::Ai(ActorOwner &owner, Actor &actor)
	:EventCom<Ai>(owner)
	, m_owner(owner)
	, m_actor(actor)
	, m_ActionStateMgr(owner, actor)
{

}
