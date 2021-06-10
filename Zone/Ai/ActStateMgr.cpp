#include "Ai.h"


ActStateMgr::ActStateMgr(ActorOwner &owner, Actor &actor)
	:EventCom<ActStateMgr>(owner)
	,m_owner(owner)
	,m_Actor(actor)
{
}

void ActStateMgr::Start()
{
	m_state = &m_WanderState;
	m_state->Enter();
	m_tm.StartTimerSec(1, &ActStateMgr::OnThink, this);
}

void ActStateMgr::OnThink()
{
	m_state->OnThink();
}

void ActStateMgr::ChangeState(ActBaseState &state)
{
	m_state->Exit();
	m_state = &state;
	m_state->Enter();
}

void CombatState::OnThink()
{

}
