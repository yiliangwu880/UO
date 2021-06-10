#include "Actor.h"

StateMgr::StateMgr(Actor &actor)
	:ActorSubCom<StateMgr>(actor.m_owner, actor)
{

}

StateMgr::~StateMgr()
{
	for (auto &v : m_all)
	{
		if (v != nullptr)
		{
			delete v;
			v = nullptr;
		}
	}

}

void StateMgr::OnDelTimer()
{
	for (uint32 &id : m_waitDelId)
	{
		if (m_all[id] != nullptr)
		{
			delete m_all[id];
			m_all[id] = nullptr;
		}
	}
}

