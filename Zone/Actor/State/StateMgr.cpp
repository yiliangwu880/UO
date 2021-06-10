#include "Actor.h"





GRegEvent(EV_SVR_CFG_INI, StateCreate::Init)
void StateCreate::Init(bool &ret)
{
#define DEF_STATE_ID(State)\
StateCreate::Ins().m_all[(uint32)StateId::State] = StateIdTrait<StateId::State>::Create;\

	ALL_STATE_ID

#undef DEF_STATE_ID
}


StateMgr::StateMgr(Actor &actor)
	:ActorSubCom<StateMgr>(actor.m_owner, actor)
{

}


BaseState * StateMgr::AddStateById(StateId id, const vector<any> &cfg)
{
	uint32 idx = (uint32)id;
	L_COND(idx < (uint32)StateId::MAX, nullptr);

	StateCreateFun f = StateCreate::Ins().m_all[idx];
	if (nullptr == m_all[idx])
	{
		shared_ptr<BaseState> p = f(m_Actor);
		m_all[idx] = p;
		p->Init(cfg);
		return p.get();
	}

	m_all[idx]->RetAdd(cfg);
	return m_all[idx].get();
}

void StateMgr::PostDel(StateId id)
{
	m_waitDelId.push_back((uint32)id);
	m_delTm.StartTimer(1, std::bind(&StateMgr::OnDelTimer, this));
}

void StateMgr::OnDelTimer()
{
	for (uint32 &id : m_waitDelId)
	{
		if (m_all[id] != nullptr)
		{
			m_all[id] = nullptr;
		}
	}
}

