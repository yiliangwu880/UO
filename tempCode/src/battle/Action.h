#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <any>


using ActionFun = void(*)(vector<any>, Actor &trigger, Actor &target) > ;
//@ActionLv 比如技能等级，buff等级，用来调整配置的系数
using ActionChgFun = vector<any> (*)(vector<any> > , int ActionLv, Actor  &actor, Actor *target) ;

namespace ActionChg
{
	vector<any> EarthQuakeLv(vector<any> cfg, int ActionLv, Actor *trigger, Actor *target)
	{
		//可以更复杂，比如根据释放者，目标等级差。改变技能等级效果
		vector<any> changeCfg = cfg;
		changeCfg[0] = changeCfg[0] * ActionLv;
		return changeCfg
	}
	//通用 changeCfg[0] * skill.lv
	vector<any> Lv0(vector<any> cfg, int ActionLv, Actor *trigger, Actor *target)
	{
		//可以更复杂，比如根据释放者，目标等级差。改变技能等级效果
		vector<any> changeCfg = cfg;
		changeCfg[0] = changeCfg[0] * ActionLv;
		return changeCfg
	}
	vector<any> Lv1(vector<any> cfg, int ActionLv, Actor *trigger, Actor *target)
	{
	}
}
namespace Action
{
	//地震
	void EarthQuake(vector<any> cfg, Actor &trigger, Actor  &target)
	{
		//aoe ,dec hp
	}
	//哈斯卡debuff
	void HaSiKaDebuff(vector<any> &cfg, Actor &trigger, Actor  &target)
	{
		//dec hp
		StateHSKDeBuffCombine *p = target->m_StateMgr.TryCreateState<StateHSKDeBuffCombine>(cfg);
		p->Add(cfg);
	}
	//类似结构，只创建State
	template<class State>
	void CreateState(vector<any> cfg, Actor &trigger, Actor  &target)
	{
		target.m_StateMgr.TryCreateState<State>(cfg);
	}	
	//通用add buff
	void AddBuf(vector<any> cfg, Actor &trigger, Actor &target)
	{
		int buffid = cfg[0];
		int buffLv = cfg[1];
		target.m_BuffMgr.TryAddBuff(buffid, buffLv, trigger, target);
	}
	//古法吸血，当buff效果处理。释放着被打断，buff消失
	void GuFaBig(vector<any> cfg, Actor &trigger, Actor &target)
	{
		int buffLv = cfg[0];
		trigger.m_BuffMgr.TryAddBuff(1, buffLv, trigger, trigger);
		target.m_BuffMgr.TryAddBuff(2, buffLv, trigger, target);
		
		StateTriggerXixue *state = trigger.m_StateMgr.GetState(StateId::StateTriggerXixue);
		state.init(target.WeakPtr());
	}

};

