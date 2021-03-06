#include "Act.h"
#include "ActCfg.h"

namespace ChgAct
{
	vector<any> EarthQuakeLv(const vector<any> &cfg, uint32 ActLv, Actor &trigger, const UnionTarget &target)
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
	vector<any> Lv0(const vector<any> &cfg, uint32 ActLv, Actor &trigger, const UnionTarget &target)
	{
		//可以更复杂，比如根据释放者，目标等级差。改变技能等级效果
		vector<any> ChgCfg = cfg;
		//ChgCfg[0] = ChgCfg[0] * ActLv;
		return ChgCfg;
	}

}

namespace Act
{

	//服务器初始化会检查配置，全部合法才能启动，运行期代码就不用检查了
	bool CheckEarthQuake(const vector<any> &cfg)
	{ 
		L_COND(cfg.size() >= 1, false);
		L_COND(any_cast<int>(&cfg[0]), false);
		return true;
	}

	MAP_REG_DEFINE(Act2Check, EarthQuake, CheckEarthQuake);
	//地震
	void EarthQuake(const vector<any> &cfg, Actor &trigger, const UnionTarget &target)
	{

	}

	bool CheckMore(const vector<any> &cfg)
	{
		L_COND(cfg.size() >= 1, false);
		for (const any &v : cfg)
		{
			L_COND(any_cast<ActCfg>(&v), false);
		}
		return true;
	}

	MAP_REG_DEFINE(Act2Check, More, CheckMore);
	void More(const vector<any> &cfg, Actor &trigger, const UnionTarget &target)
	{
		L_ERROR("no need run"); //具体实现在 ActSkill.方便传入 ActLv

	}
	////哈斯卡debuff
	//void HaSiKaDebuff(vector<any> &cfg, Actor &trigger, const UnionTarget &target)
	//{
	//	//dec hp
	//	StateHSKDeBuffCombine *p = target->m_StateMgr.TryCreateState<StateHSKDeBuffCombine>(cfg);
	//	p->Add(cfg);
	//}
	////类似结构，只创建State
	//template<class State>
	//void CreateState(vector<any> cfg, Actor &trigger, const UnionTarget &target)
	//{
	//	target.m_StateMgr.TryCreateState<State>(cfg);
	//}
	//template<class State>
	//void UpdateState(vector<any> cfg, Actor &trigger, const UnionTarget &target)
	//{
	//	target.m_StateMgr.UpdateState<State>(cfg);
	//}
	//template<class State>
	//void UpdatePassive(vector<any> cfg, Actor &target)
	//{
	//	target.m_StateMgr.UpdateState<State>(cfg);
	//}
	////通用add buff
	//void AddBuf(vector<any> cfg, Actor &trigger, const UnionTarget &target)
	//{
	//	int buffid = cfg[0];
	//	int buffLv = cfg[1];
	//	target.m_BuffMgr.TryAddBuff(buffid, buffLv, trigger, target);
	//}
	////古法吸血，当buff效果处理。释放着被打断，buff消失
	//void GuFaBig(vector<any> cfg, Actor &trigger, const UnionTarget &target)
	//{
	//	int buffLv = cfg[0];
	//	trigger.m_BuffMgr.TryAddBuff(1, buffLv, trigger, trigger);
	//	target.m_BuffMgr.TryAddBuff(2, buffLv, trigger, target);

	//	StateTriggerXixue *state = trigger.m_StateMgr.GetState(StateId::StateTriggerXixue);
	//	state.init(target.WeakPtr());
	//}
	//void CreateMonster(vector<any> cfg, Actor &trigger, const UnionTarget &target)
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