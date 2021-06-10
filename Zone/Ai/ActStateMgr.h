#pragma once
#include "Actor/Actor.h"

class ActBaseState
{
public:
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnThink()=0;
};

class CombatState : public ActBaseState
{
public:
	virtual void OnThink() override;
};

class WanderState : public ActBaseState
{
public:
	virtual void OnThink() override {};
};

class ActStateMgr : public EventCom<ActStateMgr>
{
	ActorOwner &m_owner;
	Actor &m_Actor;
	lc::Timer m_tm;
	ActBaseState *m_state=nullptr;//状态机
	CombatState m_CombatState;
	WanderState m_WanderState;
public:
	ActStateMgr(ActorOwner &owner, Actor &actor);
	void Start();
	void OnThink();

	void ChangeState(ActBaseState &state);
	template<class State>
	bool IsState()
	{
		State *p = dynamic_cast<State *>(m_state);
		return  (NULL != p);
	}
};