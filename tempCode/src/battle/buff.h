/*
buff debuff实现。
buff对象 拥有actor的state
*/
#pragma once
 
#include <vector>
#include <map>
#include <functional>
#include <memory>
#include "com.h"
#include "cfg.h"

enum class BuffId
{
	TriggerXixue,
	TargetXixue,

};

class BuffMgr
{
	Actor m_owner;
	std::unordered_map<int, Buff> m_id2buff;
public:
	bool TryAddBuff(int buffId, int buffLv, Actor &trigger, Actor &target)
	{
		BuffCfg cfg = GetBuffCfg();
		if (m_owner.isBkb )
		{
			return false
		}
		m_id2buff[buffId] = Buff(m_owner);
		m_id2buff[buffId].Init(buffId, buffLv, Actor &trigger, Actor &target);
	}
	bool Remove(int buffId);
	BuffCfg GetBuffCfg();
};
//通用buff,不同效果根据buffId区别。 buffId关联 m_StateId
class Buff
{
	Actor m_owner;
	su::Timer tm; //cd
	int m_buffId;//map cfg,  map StateId m_StateId;
	
public:
	Buff(Actor &actor)
		:m_owner(owner)
	{}
	~Buff()
	{
		m_owner.m_StateMgr.Remove(GetStateId());
	}
	StateId GetStateId();
	BuffCfg GetBuffCfg();
	//地震,哈斯卡debuff,普通攻击技能 ， 。。。
	void Init(int buffId, int buffLv, Actor &trigger, Actor &target)
	{
		m_buffId = buffId;
		BuffCfg cfg = GetBuffCfg();
		ActEffect ae = cfg.ae;
		auto anys = ae.chgFun(ae.anys, buffLv, trigger, m_owner);
		(*ae.action)(ae.anys, trigger, m_owner);
	}

private:
};
