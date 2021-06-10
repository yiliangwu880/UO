//管理 actor身上所有动态状态
#pragma once
#include "State.h"

class StateMgr : public ActorSubCom<StateMgr>
{
	std::array<BaseState *, (uint32)StateId::MAX> m_all; //id 2 State
	VecUint32 m_waitDelId;
	lc::Timer m_delTm;
public:
	StateMgr(Actor &actor);
	~StateMgr();

	template<class State>
	State *GetState()
	{
		if (m_all[StateTrait<State>::ID] == nullptr)
		{
			return nullptr;
		}
		State *p = dynamic_cast<State *>(m_all[StateTrait<State>::ID]);
		L_COND(p, nullptr, "dif state type use same id?");
		return p;
	}

	//注意： 直接删除后， 别引用野指针
	template<class State>
	bool Del(State *p)
	{
		if (m_all[StateTrait<State>::ID] != nullptr)
		{
			delete m_all[StateTrait<State>::ID];
			m_all[StateTrait<State>::ID] = nullptr;
			return true;
		}
		return false;
	}

	template<class State>
	void PostDel(State *p)
	{
		m_waitDelId.push_back(StateTrait<State>::ID);
		m_delTm.StartTimer(1, std::bind(&StateMgr::OnDelTimer, this));
	}

	//加状态，返回新的或者旧的
	template<class State>
	State *AddState(const vector<any> &cfg)
	{
		if (nullptr == m_all[StateTrait<State>::ID])
		{
			State *p = new State(m_Actor);
			m_all[StateTrait<State>::ID] = p;
			p->Init(cfg);
			return p;
		}

		State *old = dynamic_cast<State *>(m_all[StateTrait<State>::ID]);
		L_COND(old, nullptr, "dif state type use same id?");
		old->RetAdd(cfg);
		return old;
	}

private:
	void OnDelTimer();

};
