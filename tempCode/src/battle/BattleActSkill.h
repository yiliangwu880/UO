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
	std::map<int, BattleActSkill> m_id2Skill;
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
	void Update(int id);
}



//ս���������ܣ������ͷ�
class BattleActSkill
{
	Actor m_owner;
public:
	static const int ID = 1;
	int id, lv;

	void Use(Actor *target)
	{
		BattleActSkillCfg cfg = skill.GetSkillCfg();
		for (ActEffect ae : cfg.vecAe)
		{
			ActActorFun *pActActorFun = ae.actions[0]._Cast<ActActorFun>();
			if (ActActorFun)
			{
				ActActorChgFun *pActActorChgFun = ae.actions[1]._Cast<ActActorChgFun>();
				auto anys = (*pActActorChgFun)(ae.anys, lv, m_owner, target);
				(*pActActorFun)(ae.anys, m_owner, target);
			}
			else if (ActFun *pActFun = ae.actions[0]._Cast<ActFun>())
			{
				ActChgFun *pActChgFun = ae.actions[1]._Cast<ActChgFun>();
				auto anys = (*pActChgFun)(ae.anys, lv, m_owner, target);
				UnionTarget d{target , 0 , 0};
				(*pActFun)(ae.anys, m_owner, d);
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
		BattleActSkillCfg cfg = skill.GetSkillCfg();
		for (ActEffect ae : cfg.vecAe)
		{
			ActActorFun *pActActorFun = ae.actions[0]._Cast<ActActorFun>();
			if (ActActorFun)
			{
				error
			}
			else if (ActFun *pActFun = ae.actions[0]._Cast<ActFun>())
			{
				ActChgFun *pActChgFun = ae.actions[1]._Cast<ActChgFun>();
				auto anys = (*pActChgFun)(ae.anys, lv, m_owner, target);
				UnionTarget d{ nullptr, x , y };
				(*pActFun)(ae.anys, m_owner, d);
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
	const BattleActSkillCfg &GetSkillCfg()
	{
		return allBattleActSkillCfg[ID];
	}

private:
};
