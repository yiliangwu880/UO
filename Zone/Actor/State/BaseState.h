#pragma once
#include "ActorSubCom.h"



enum class StateId
{
	State1 = 0,
	StateHSKDeBuffCombine,
	StateTriggerXixue,
	StateTargetXixue,
	MAX,
};

//为什么需要这个？ 用这个模板特列 + 宏 些绑定  State type 2 State ID.能容易编译期检查释放重定义。 
//特点 很好保证1对1，防止写错代码.
//不然手动写ID容易 1对多。编译器检查不出来
//错误写法例子：
//class State1 : public BaseState, public ActorSubCom<State1>
//{
//public:
//	const static uint32 ID = (uint32)StateId::State2; //state1 绑定 state2 id了！！！！
//

template<class State>
struct StateTrait
{//不定义，忘记写绑定旧编译有报错
};
#define DEF_STATE_ID(State)\
template<>\
struct StateTrait<State>\
{\
	const static uint32 ID = (uint32)StateId::State;\
};\


class BaseState 
{
public:
	virtual ~BaseState() {};
	//已经有该状态，再加一次就是重加, 默认不能重加
	virtual void RetAdd(const vector<any> &cfg) {};
};

