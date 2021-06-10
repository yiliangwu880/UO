#pragma once
#include "BaseState.h"

//例如死骑大，
class State1 : public BaseState, public ActorSubCom<State1>
{
public:
	const static uint32 ID = (uint32)StateId::State1;

public:
	State1(Actor &actor);
	virtual void Init(const vector<any> &cfg) override;
	void Fun();
	void OnSave(DbPlayer &data);
private:

};


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

	virtual void Init(const vector<any> &cfg) override;
private:

};


