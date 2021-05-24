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
	int hits, mana;
	int def, at;
};

//��ս�������ĵ�λ ����
class Actor : public BaseWeak<Actor>
{
public:
	EventMgr m_owner;
	SceneEntity m_ScenePlayer; //ʵ�峡����Ұ����
	BaseAttr attr;
	StateMgr m_StateMgr;
	BuffMgr m_BuffMgr;
	SkillMgr m_SkillMgr;
	Ai m_Ai;
	EquipMgr m_EquipMgr;//����
	Aspect m_Aspect;//���
	CorpseCreator m_CorpseCreator; //ʵ�幹�����������Ͷ಻�࣬���Ͳ���Ͳ���������ñ���+����
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

