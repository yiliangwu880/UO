#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>




class BaseState: public EventReg
{
	Actor m_owner;
public:
	BaseState(Actor &owner)
		:EventReg(owner.m_owner)//owner.m_owner最高层管理者，比如player, monster, npc
	{}

};

//ID 2 TYPE
template<int ID>
struct StateIDTrait {
	using Fun = int;
};

//死骑大，
template<>
struct StateIDTrait<StateId::State1> {
	using Type State1;
};
class State1 : public BaseState
{
public:
	const static ID = StateId::State1;

public:
	State1(Actor &owner, std::vector<any> cfg)
		:BaseState(owner)
	{
		Reg<InsEventId::ChangeHp>(ChangeHp);
	}
private:
	void ChangeHp(int &update)
	{
		if (m_owner.attr.hp<30 && update <0)
		{
			update = -update;
		}

		//if (1)//when end event state
		//{
		//	UnReg<ChangeHp>(EventCb);
		//}

	}
};

//cpp 静态注册 构造器
use define : RegFactor(StateId::State1, State1) 简化 RegFactor(State1)


//多重效果同时独立存在的 state，比如哈斯卡 debuff
class StateHSKDeBuff : public BaseState
{
	su::Timer mt;
public:
	StateHSKDeBuff(Actor &owner)
		:BaseState(owner)
	{
		mt.StartTimer(OnTImer);
	}
private:
	void OnTImer()
	{
		//dec hp
	}
};

template<>
struct StateIDTrait<StateId::StateHSKDeBuffCombine> {
	using Type StateHSKDeBuffCombine;
};
class StateHSKDeBuffCombine : public BaseState
{
	vector<StateHSKDeBuff> m_vec;
public:
	const static ID = StateId::StateHSKDeBuffCombine;
public:
	StateHSKDeBuffCombine(Actor &owner, std::vector<any> cfg)
		:BaseState(owner)
	{
	}

	virtual void Add(vector<any> &cfg) override;
	{
		m_vec[x].init(cfg);
	}
private:
	
};


template<>
struct StateIDTrait<StateId::StateTriggerXixue> {
	using Type StateTriggerXixue;
};
class StateTriggerXixue : public BaseState
{
public:
	const static ID = StateId::StateTriggerXixue;
	std::weak_ptr<Actor> m_target; //弱引用，不怕野。 .lock()获取的share_ptr别传递出去，只能栈变量使用。
public:
	StateTriggerXixue(Actor &owner, std::vector<any> cfg)
		:BaseState(owner)
	{
		Reg<InsEventId::InterUp>(InterUP);
	}
	void Init(std::weak_ptr<Actor> target)
	{
		m_target = target;
	}

private:
	void InterUP()
	{
		m_owner.m_BuffMgr.Remove(BuffId::TriggerXixue); //被打断，删除buff,间接删除this. 删除敌方buff
		shared_ptr<Actor> target = m_target.lock();
		target->m_BuffMgr.Remove(BuffId::TargetXixue);
	}
	void OnTimter()
	{
		//add hp, dec target hp
	}

};

template<>
struct StateIDTrait<StateId::StateTargetXixue> {
	using Type StateTargetXixue;
};
class StateTargetXixue : public BaseState
{
public:
	const static ID = StateId::StateTriggerXixue;
public:
	StateTargetXixue(Actor &owner, std::vector<any> cfg)
		:BaseState(owner)
	{
	}

private:

};