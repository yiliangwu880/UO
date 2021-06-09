/*
*/
#pragma once

#include <vector>
#include <map>
#include <functional>
#include "com.h"
#include "cfg.h"


//���� Uo�����ģ���Ŷ��յļ���
class Skill
{
	Player m_owner;
	int lv;
public:
	void OnLv()
	{
		if (isBattleActSkill)
		{
			int skillId = get from cfg;
			m_owner.m_Actor.m_SkillMgr.Update(id);
		}
		else if (PassiveSkillCfg)
		{
			UpdatePassiveSkill();
		}
	}
	//���±�������
	void UpdatePassiveSkill()
	{
		PassiveSkillCfg cfg = get by id;
		for (ActionEffect ae : cfg.vecAe)
		{
			UpdatePassiveFun *pFun = ae.actions[0]._Cast<UpdatePassiveFun>();
			UpdatePassiveChgFun *pChgFun = ae.actions[1]._Cast<UpdatePassiveChgFun>();
			auto anys = (*pChgFun)(ae.anys, lv);
			(*pFun)(ae.anys, m_owner.m_Actor);
		}
	}
};