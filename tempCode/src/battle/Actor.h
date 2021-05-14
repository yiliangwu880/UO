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

//��ս�������ĵ�λ ����
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
		m_SkillMgr.UseSkill(skillId, target);
	}
	void HandleCastSkill(int skillId, int x)
	{
		//...
		m_SkillMgr.UseSkill(skillId, x);
	}
	void ChangeHp(int update)
	{
		FireEvent<InsEventId::ChangeHp>(update);
		hp += update;
	}
private:
};

