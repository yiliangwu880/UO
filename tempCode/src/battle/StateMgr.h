#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>
#include "State.h"

enum class StateId
{
	State1,
	StateHSKDeBuffCombine,
	StateTriggerXixue,
	StateTargetXixue,

};

class StateMgr : public ActorSubSys
{
public:
	StateMgr()
	{
	}
	~StateMgr()
	{
		delete all state;
	}

private:
	std::vector<BaseState *> m_vecState; //id 2 State
public:
	BaseState *GetState(int Id)
	{
		return m_vecState[id];
	}
	template<class State>
	BaseState *GetState()
	{
		int id = StateTrait<State>::ID;
		return m_vecState[id];
	}
	bool Remove(StateId id)
	{
		delete m_vecState[State::ID];
	}

	template<int State>
	typename State *TryCreateState(std::vector<any> cfg, bool enableReplace)
	{
		using StateType = typename StateIDTrait<id>::Type;
		BaseState *old = GetState();
		if (old)
		{
			if (enableReplace)
			{
				auto p = new State(m_owner, cfg);
				m_vecState[State::ID] = p;
				return p;
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			auto p = State(m_owner, cfg);
			m_vecState[id] = p;
			return p;
		}
	}
	

	void UserSimple()
	{
		//BaseState * p = CreateState(id);
		BaseState * p = GetState(id);
		if (singleState)
		{
			p->Init(cfg);
		}
		else
		{
			p->Add(cfg);
		}
	}
private:
}
