#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <any>

//����Ŀ�꣬��ѡһ
struct UnionTarget
{
	Actor *target = nullptr;
	int x, y;//����
};

//Ŀ��ֻ����Actor����nullptr
using ActionActorFun = void(*)(vector<any>, Actor &trigger, Actor *target) > ;
//@ActionLv ���缼�ܵȼ���buff�ȼ��������������õ�ϵ��
using ActionActorChgFun = vector<any>(*)(vector<any> > , int ActionLv, Actor  &actor, Actor *target);

using ActionFun = void(*)(vector<any>, Actor &trigger, UnionTarget &target) > ;
//@ActionLv ���缼�ܵȼ���buff�ȼ��������������õ�ϵ��
using ActionChgFun = vector<any> (*)(vector<any> > , int ActionLv, Actor  &actor, UnionTarget &target) ;


//�������ܸ���
using UpdatePassiveFun = void(*)(vector<any>, Actor &target) > ;
//@ActionLv ���缼�ܵȼ���buff�ȼ��������������õ�ϵ��
using UpdatePassiveChgFun = vector<any>(*)(vector<any> > , int ActionLv);


namespace ActionChg
{
	vector<any> EarthQuakeLv(vector<any> cfg, int ActionLv, Actor *trigger, UnionTarget &target)
	{
		//���Ը����ӣ���������ͷ��ߣ�Ŀ��ȼ���ı似�ܵȼ�Ч��
		vector<any> changeCfg = cfg;
		changeCfg[0] = changeCfg[0] * ActionLv;
		return changeCfg
	}
	//ͨ�� changeCfg[0] * skill.lv
	vector<any> Lv0(vector<any> cfg, int ActionLv, Actor *trigger, Actor *target)
	{
		//���Ը����ӣ���������ͷ��ߣ�Ŀ��ȼ���ı似�ܵȼ�Ч��
		vector<any> changeCfg = cfg;
		changeCfg[0] = changeCfg[0] * ActionLv;
		return changeCfg
	}
	vector<any> Lv1(vector<any> cfg, int ActionLv, Actor *trigger, Actor *target)
	{
	}
}


namespace PassiveChg
{

	//ͨ�� changeCfg[0] * skill.lv
	vector<any> Lv0(vector<any> cfg, int ActionLv)
	{
		//���Ը����ӣ���������ͷ��ߣ�Ŀ��ȼ���ı似�ܵȼ�Ч��
		vector<any> changeCfg = cfg;
		changeCfg[0] = changeCfg[0] * ActionLv;
		return changeCfg
	
	vector<any> Lv1(vector<any> cfg, int ActionLv, Actor *trigger, Actor *target)
	{
	}
}

namespace Action
{
	//����
	void EarthQuake(vector<any> cfg, Actor &trigger, Actor *target)
	{
		//aoe ,dec hp
	}
	//��˹��debuff
	void HaSiKaDebuff(vector<any> &cfg, Actor &trigger, Actor *target)
	{
		//dec hp
		StateHSKDeBuffCombine *p = target->m_StateMgr.TryCreateState<StateHSKDeBuffCombine>(cfg);
		p->Add(cfg);
	}
	//���ƽṹ��ֻ����State
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
	//ͨ��add buff
	void AddBuf(vector<any> cfg, Actor &trigger, Actor *target)
	{
		int buffid = cfg[0];
		int buffLv = cfg[1];
		target.m_BuffMgr.TryAddBuff(buffid, buffLv, trigger, target);
	}
	//�ŷ���Ѫ����buffЧ�������ͷ��ű���ϣ�buff��ʧ
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

