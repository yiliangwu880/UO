#pragma once
#include "Actor/Actor.h"

class ActionBaseState
{
public:
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnThink()=0;
};

class CombatState : public ActionBaseState
{
public:
	virtual void OnThink() override;
};

class WanderState : public ActionBaseState
{
public:
	virtual void OnThink() override {};
};

class ActionStateMgr : public EventCom<ActionStateMgr>
{
	ActorOwner &m_owner;
	Actor &m_Actor;
	lc::Timer m_tm;
	ActionBaseState *m_state=nullptr;//状态机
	CombatState m_CombatState;
	WanderState m_WanderState;
public:
	ActionStateMgr(ActorOwner &owner, Actor &actor);
	void Start();
	void OnThink();
};