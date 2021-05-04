/*
���ܿ��Բ��������������еȼ����ԣ��ȼ��߲�������Ч������
*/
#pragma once

#include <vector>
#include <map>
#include <functional>
#include "com.h"
#include "cfg.h"

class SkillMgr
{
	Actor m_owner;
	std::map<int, Skill> m_id2Skill;
public:
	//����,��˹��debuff,��ͨ�������� �� ������
	void UseSkill(int skillId, Actor *target)
	{
		m_id2Skill[skillId].Use(target);
	}
	void UseSkill(int skillId, int x)
	{
		m_id2Skill[skillId].Use(x);
	}

}
class Skill
{
	Actor m_owner;
public:
	static const int ID = 1;
	int id, lv;

	void Use(Actor *target)
	{
		SkillCfg cfg = skill.GetSkillCfg();
		for (ActionEffect ae : cfg.vecAe)
		{
			ActionActorFun *pActionActorFun = ae.actions[0]._Cast<ActionActorFun>();
			if (ActionActorFun)
			{
				ActionActorChgFun *pActionActorChgFun = ae.actions[1]._Cast<ActionActorChgFun>();
				auto anys = (*pActionActorChgFun)(ae.anys, lv, m_owner, target);
				(*pActionActorFun)(ae.anys, m_owner, target);
			}
			else if (ActionFun *pActionFun = ae.actions[0]._Cast<ActionFun>())
			{
				ActionChgFun *pActionChgFun = ae.actions[1]._Cast<ActionChgFun>();
				auto anys = (*pActionChgFun)(ae.anys, lv, m_owner, target);
				UnionTarget d{target , 0 , 0};
				(*pActionFun)(ae.anys, m_owner, d);
			}
			else
			{
				error
			}
		}
		//�л������� lv++;
		if (m_owner.type == Player)
		{
			lv++;
		}
	}	
	void Use(int  xy)
	{
		SkillCfg cfg = skill.GetSkillCfg();
		for (ActionEffect ae : cfg.vecAe)
		{
			ActionActorFun *pActionActorFun = ae.actions[0]._Cast<ActionActorFun>();
			if (ActionActorFun)
			{
				error
			}
			else if (ActionFun *pActionFun = ae.actions[0]._Cast<ActionFun>())
			{
				ActionChgFun *pActionChgFun = ae.actions[1]._Cast<ActionChgFun>();
				auto anys = (*pActionChgFun)(ae.anys, lv, m_owner, target);
				UnionTarget d{ nullptr, x , y };
				(*pActionFun)(ae.anys, m_owner, d);
			}
			else
			{
				error
			}
		}
		//�л������� lv++;
		if (m_owner.type == Player)
		{
			lv++;
		}
	}
	const SkillCfg &GetSkillCfg()
	{
		return allSkillCfg[ID];
	}

private:
};
