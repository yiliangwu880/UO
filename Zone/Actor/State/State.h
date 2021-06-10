#pragma once
#include "BaseState.h"





//例如死骑大，
class State1 : public BaseState, public ActorSubCom<State1>
{
public:
	const static uint32 ID = (uint32)StateId::State1;

public:
	State1(Actor &actor);
	void Init(const vector<any> &cfg);
	void Fun();
	void OnSave(DbPlayer &data);
private:

};
DEF_STATE_ID(State1);

//多重效果同时独立存在的 state，比如哈斯卡 debuff
class StateHSKDeBuff : public BaseState, public ActorSubCom<StateHSKDeBuff>
{
	lc::Timer mt;
public:
	StateHSKDeBuff(Actor &actor);
		//
	
private:
	void OnTImer()
	{
		//dec hp
	}
};

class StateHSKDeBuffCombine : public BaseState, public ActorSubCom<StateHSKDeBuffCombine>
{
	vector<StateHSKDeBuff *> m_vec;

public:
	StateHSKDeBuffCombine(Actor &actor);

	void Init(const vector<any> &cfg);
private:

};
DEF_STATE_ID(StateHSKDeBuffCombine);

