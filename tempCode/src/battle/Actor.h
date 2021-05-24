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

//能战斗互动的单位 管理
class Actor : public BaseWeak<Actor>
{
public:
	EventMgr m_owner;
	SceneEntity m_ScenePlayer; //实体场景视野管理
	BaseAttr attr;
	StateMgr m_StateMgr;
	BuffMgr m_BuffMgr;
	SkillMgr m_SkillMgr;
	Ai m_Ai;
	EquipMgr m_EquipMgr;//穿戴
	Aspect m_Aspect;//外观
	CorpseCreator m_CorpseCreator; //实体构造器，看类型多不多，类型不多就不用这个，用变量+函数
public:
	~Actor()
	{
	}
	EventMgr &GetEventMgr()
	{
		m_owner.GetEventMgr();
	}

	//系统事件，出发释放技能
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

