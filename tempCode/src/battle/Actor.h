`	#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <any>
#include "cfg.h"

struct BaseAttr
{
	int str, dec, ini;
	int hp, mana;
	int def, at;
};

//��ս������������
class Actor : public BaseWeak<Actor>
{
public:
	EventMgr m_owner;
	BaseAttr attr;
	StateMgr m_StateMgr;
	BuffMgr m_BuffMgr;
	SkillMgr m_SkillMgr;
public:
	~Actor()
	{
	}
	EventMgr &GetEventMgr()
	{
		m_owner.GetEventMgr();
	}

	//ϵͳ�¼��������ͷż���
	void HandleCastSkill(int skillId, Actor *target)
	{	
		//...
		//m_SkillMgr.UseSkill

	}
	void ChangeHp(int update)
	{
		FireEvent<ActorEventId::ChangeHp>(update);
		hp += update;
	}
private:
};

