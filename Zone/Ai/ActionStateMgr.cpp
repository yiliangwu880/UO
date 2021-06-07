#include "Ai.h"


ActionStateMgr::ActionStateMgr(ActorOwner &owner, Actor &actor)
	:EventCom<ActionStateMgr>(owner)
	,m_owner(owner)
	,m_actor(actor)
{
}

void ActionStateMgr::Start()
{
	m_state = &m_WanderState;
	m_state->Enter();
	m_tm.StartTimerSec(1, &ActionStateMgr::OnThink, this);
}

void ActionStateMgr::OnThink()
{
	m_state->OnThink();
}

void CombatState::OnThink()
{

}
