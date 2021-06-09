#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <any>

//联合目标，多选一
struct UnionTarget
{
	Actor *target = nullptr;
	int x, y;//坐标
};

//目标只能是Actor或者nullptr
using ActActorFun = void(*)(vector<any>, Actor &trigger, Actor *target) > ;
//调整 ActActorFun 的输入参数
//@ActLv 比如技能等级，buff等级，对方属性，用来调整配置的系数
using ChgActActorParaFun = vector<any>(*)(vector<any> > , int ActLv, Actor  &actor, Actor *target);

using ActFun = void(*)(vector<any>, Actor &trigger, UnionTarget &target) > ;
//@ActLv 比如技能等级，buff等级，用来调整配置的系数
using ChgActParaFun = vector<any> (*)(vector<any> > , int ActLv, Actor  &actor, UnionTarget &target) ;

//不要，改用 ActActorFun ChgActActorParaFun
//被动技能更新，
using UpdatePassiveFun = void(*)(vector<any>, Actor &target) > ;
//@ActLv 比如技能等级，buff等级，用来调整配置的系数
using UpdatePassiveChgFun = vector<any>(*)(vector<any> > , int ActLv);


namespace ActChg
{
	vector<any> EarthQuakeLv(vector<any> cfg, int ActLv, Actor *trigger, UnionTarget &target)
	{
		//可以更复杂，比如根据释放者，目标等级差。改变技能等级效果
		vector<any> changeCfg = cfg;
		changeCfg[0] = changeCfg[0] * ActLv;
		return changeCfg
	}
	//通用 changeCfg[0] * skill.lv
	vector<any> Lv0(vector<any> cfg, int ActLv, Actor *trigger, Actor *target)
	{
		//可以更复杂，比如根据释放者，目标等级差。改变技能等级效果
		vector<any> changeCfg = cfg;
		changeCfg[0] = changeCfg[0] * ActLv;
		return changeCfg
	}
	vector<any> Lv1(vector<any> cfg, int ActLv, Actor *trigger, Actor *target)
	{
	}
}


namespace PassiveChg
{

	//通用 changeCfg[0] * skill.lv
	vector<any> Lv0(vector<any> cfg, int ActLv)
	{
		//可以更复杂，比如根据释放者，目标等级差。改变技能等级效果
		vector<any> changeCfg = cfg;
		changeCfg[0] = changeCfg[0] * ActLv;
		return changeCfg
	
	vector<any> Lv1(vector<any> cfg, int ActLv, Actor *trigger, Actor *target)
	{
	}
}

namespace Act
{
	//地震
	void EarthQuake(vector<any> cfg, Actor &trigger, Actor *target)
	{
		//aoe ,dec hp
	}
	//哈斯卡debuff
	void HaSiKaDebuff(vector<any> &cfg, Actor &trigger, Actor *target)
	{
		//dec hp
		StateHSKDeBuffCombine *p = target->m_StateMgr.TryCreateState<StateHSKDeBuffCombine>(cfg);
		p->Add(cfg);
	}
	//类似结构，只创建State
	template<class State>
	void CreateState(vector<any> cfg, Actor &trigger, Actor *target)
	{
		target.m_StateMgr.TryCreateState<State>(cfg);
	}	
	template<class State>
	void UpdateState(vector<any> cfg, Actor &trigger, Actor *target)
	{
		target.m_StateMgr.UpdateState<State>(cfg);
	}
	template<class State>
	void UpdatePassive(vector<any> cfg, Actor &target)
	{
		target.m_StateMgr.UpdateState<State>(cfg);
	}
	//通用add buff
	void AddBuf(vector<any> cfg, Actor &trigger, Actor *target)
	{
		int buffid = cfg[0];
		int buffLv = cfg[1];
		target.m_BuffMgr.TryAddBuff(buffid, buffLv, trigger, target);
	}
	//古法吸血，当buff效果处理。释放着被打断，buff消失
	void GuFaBig(vector<any> cfg, Actor &trigger, Actor *target)
	{
		int buffLv = cfg[0];
		trigger.m_BuffMgr.TryAddBuff(1, buffLv, trigger, trigger);
		target.m_BuffMgr.TryAddBuff(2, buffLv, trigger, target);
		
		StateTriggerXixue *state = trigger.m_StateMgr.GetState(StateId::StateTriggerXixue);
		state.init(target.WeakPtr());
	}
	void CreateMonster(vector<any> cfg, Actor &trigger, UnionTarget &target)
	{
		if (target.target != nullptr)
		{
			create monster in target.target->attr.x, y;
		}
		else 
		{
			create monster in position
		}
	}
};

