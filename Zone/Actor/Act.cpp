#include "Act.h"

namespace ChgAct
{
	vector<any> EarthQuakeLv(const vector<any> &cfg, uint32 ActLv, Actor &trigger, UnionTarget &target)
	{
		//可以更复杂，比如根据释放者，目标等级差。改变技能等级效果
		vector<any> ChgCfg = cfg;
		L_COND(ChgCfg.size() > 1, vector<any>());
		uint16 *p0 = any_cast<uint16>(&ChgCfg[0]);
		L_COND(p0, vector<any>());

		ChgCfg[0] = *p0 * ActLv;

		return ChgCfg;
	}
	//通用 ChgCfg[0] * skill.lv
	vector<any> Lv0(const vector<any> &cfg, uint32 ActLv, Actor &trigger, UnionTarget &target)
	{
		//可以更复杂，比如根据释放者，目标等级差。改变技能等级效果
		vector<any> ChgCfg = cfg;
		//ChgCfg[0] = ChgCfg[0] * ActLv;
		return ChgCfg;
	}

}

namespace Act
{

	//地震
	void EarthQuake(const vector<any> &cfg, Actor &trigger, UnionTarget &target)
	{

	}

	////哈斯卡debuff
	//void HaSiKaDebuff(vector<any> &cfg, Actor &trigger, UnionTarget &target)
	//{
	//	//dec hp
	//	StateHSKDeBuffCombine *p = target->m_StateMgr.TryCreateState<StateHSKDeBuffCombine>(cfg);
	//	p->Add(cfg);
	//}
	////类似结构，只创建State
	//template<class State>
	//void CreateState(vector<any> cfg, Actor &trigger, UnionTarget &target)
	//{
	//	target.m_StateMgr.TryCreateState<State>(cfg);
	//}
	//template<class State>
	//void UpdateState(vector<any> cfg, Actor &trigger, UnionTarget &target)
	//{
	//	target.m_StateMgr.UpdateState<State>(cfg);
	//}
	//template<class State>
	//void UpdatePassive(vector<any> cfg, Actor &target)
	//{
	//	target.m_StateMgr.UpdateState<State>(cfg);
	//}
	////通用add buff
	//void AddBuf(vector<any> cfg, Actor &trigger, UnionTarget &target)
	//{
	//	int buffid = cfg[0];
	//	int buffLv = cfg[1];
	//	target.m_BuffMgr.TryAddBuff(buffid, buffLv, trigger, target);
	//}
	////古法吸血，当buff效果处理。释放着被打断，buff消失
	//void GuFaBig(vector<any> cfg, Actor &trigger, UnionTarget &target)
	//{
	//	int buffLv = cfg[0];
	//	trigger.m_BuffMgr.TryAddBuff(1, buffLv, trigger, trigger);
	//	target.m_BuffMgr.TryAddBuff(2, buffLv, trigger, target);

	//	StateTriggerXixue *state = trigger.m_StateMgr.GetState(StateId::StateTriggerXixue);
	//	state.init(target.WeakPtr());
	//}
	//void CreateMonster(vector<any> cfg, Actor &trigger, UnionTarget &target)
	//{
	//	if (target.target != nullptr)
	//	{
	//		create monster in target.target->attr.x, y;
	//	}
	//	else
	//	{
	//		create monster in position
	//	}
	//}

}