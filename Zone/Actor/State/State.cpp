#include "Actor.h"




void State1::Fun()
{

}

State1::State1(Actor &actor)
	: ActorSubCom<State1>(actor.m_owner, actor)
{
	Reg<EV_BEFORE_LOGIN>(&State1::Fun);
	Reg<EV_SAVE_DB>(&State1::OnSave);
}

void State1::Init(const vector<any> &cfg)
{
	m_Actor.m_StateMgr.GetState<State1>();
}

void State1::OnSave(DbPlayer &data)
{

}

StateHSKDeBuff::StateHSKDeBuff(Actor &actor)
	: ActorSubCom<StateHSKDeBuff>(actor.m_owner, actor)
{
	mt.StartTimerSec(1, &StateHSKDeBuff::OnTImer, this);
	Reg<EV_BEFORE_LOGIN>(&StateHSKDeBuff::OnTImer);
}

StateHSKDeBuffCombine::StateHSKDeBuffCombine(Actor &actor)
	: ActorSubCom<StateHSKDeBuffCombine>(actor.m_owner, actor)
{

}

void StateHSKDeBuffCombine::Init(const vector<any> &cfg)
{
	//m_vec.push_back()
}
