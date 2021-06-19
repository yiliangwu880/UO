#include "Actor.h"
#include "State/StateMgr.h"

BuffMgr::BuffMgr(Actor &actor)
	:ActorSubCom<BuffMgr>(actor.m_owner, actor)
{

}

bool BuffMgr::AddBuff(BuffId id, uint16 lv, Actor &trigger, Actor &target)
{
	auto it = m_id2buff.find(id);
	if (it != m_id2buff.end())
	{
		auto p = it->second;
		if (p->GetLv() >= lv)
		{
			return false;
		}
		m_id2buff.erase(it);
	}
	auto p = make_shared<Buff>(m_Actor);
	m_id2buff.emplace(std::make_pair(id, p));
	p->Init(id, lv);
	return true;
}

void BuffMgr::Del(BuffId id)
{
	auto it = m_id2buff.find(id);
	if (it != m_id2buff.end())
	{
		m_id2buff.erase(it);
	}
}

Buff::Buff(Actor &actor)
	:m_Actor(actor)
{

}

void Buff::Init(BuffId id, uint16 lv)
{
	m_cfg = gCfg.GetBuffCfg(id);
	L_COND_V(m_cfg);

	m_tm.StartTimerSec(m_cfg->sec, &Buff::OnTimerOut, this);
	if (m_cfg->state.id == StateId::More)
	{
		for (const any &v : m_cfg->state.paras)
		{
			const BuffState *pBuffState = any_cast<BuffState>(&v);
			m_Actor.m_StateMgr.AddStateById(pBuffState->id, pBuffState->paras);
		}
	}
	else
	{
		m_Actor.m_StateMgr.AddStateById(m_cfg->state.id, m_cfg->state.paras);
	}
}

void Buff::OnTimerOut()
{
	m_Actor.m_BuffMgr.Del(m_buffId);
	//this 被删除了，不要再访问。
}
