//管理 actor身上所有动态状态
#pragma once
#include "State.h"
#include "StateDef.h"

using StateCreateFun = shared_ptr<BaseState> (*)(Actor &actor);

struct StateCreate : public Singleton<StateCreate>
{
	std::array<StateCreateFun, (uint32)StateId::MAX> m_all;
	static void Init(bool &ret);
};

class StateMgr : public ActorSubCom<StateMgr>
{
	std::array<shared_ptr<BaseState>, (uint32)StateId::MAX> m_all; //id 2 State . //优先安全，不考虑效率，不用new
	VecUint32 m_waitDelId;
	lc::Timer m_delTm;
public:
	StateMgr(Actor &actor);

	BaseState *AddStateById(StateId id, const vector<any> &cfg);

	template<class State>
	State *GetState()
	{
		if (m_all[StateTrait<State>::ID] == nullptr)
		{
			return nullptr;
		}
		State *p = dynamic_cast<State *>(m_all[StateTrait<State>::ID].get());
		L_COND(p, nullptr, "dif state type use same id?");
		return p;
	}



	void PostDel(StateId id);



private:
	void OnDelTimer();

};


#define DEF_STATE_ID(State)\
template<>\
struct StateTrait<State>\
{\
	const static uint32 ID = (uint32)StateId::State;\
};\
\
template<>\
struct StateIdTrait<StateId::State>\
{\
	static shared_ptr<BaseState> Create(Actor &actor)\
	{\
		return make_shared<State>(actor);\
	}\
};\
\

	ALL_STATE_ID

#undef DEF_STATE_ID
