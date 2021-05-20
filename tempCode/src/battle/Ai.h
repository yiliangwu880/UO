#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>

public enum ActionType
{
	Wander,
	Combat,
	Guard,
	Flee,
	Backoff,
	Interact
}

class BaseSpeedAi
{

};
class BaseActionAi
{

};
class BaseSkillAi
{

};

//组件组合成整体AI。
//每个组件用状态机模式
//避免可以组合的状态合并都有状态机。例如 ：1战斗状态：进攻，逃跑。。。 2技能状态：释放，等待。。。  不要合并
class Ai
{
	Actor &m_actor;
	BaseSkillAi m_SkillAi;
	BaseActionAi m_ActionAi;
	BaseSpeedAi m_SpeedAi;
public:

	//自我驱动
	void OnTimer()
	{
		case state, do Action;
		Think();
	}
	//外部驱动
	void OnTalk()
	{
		case state, do speech something;
	}
};