#include "Actor.h"

ActSkill::ActSkill(Actor &actor)
	:ActorSubCom<ActSkill>(actor.m_owner, actor)
{

}

void ActSkill::Act(uint32 id, const UnionTarget &target)
{
	auto it = m_id2lv.find(id);
	L_COND_V(it != m_id2lv.end());
	uint32 lv = it->second;
	const ActCfg *cfg = gCfg.GetActCfgMgr(id);
	L_COND_V(cfg);


	if(cfg->act == Act::More)
	{
		for (const any &v : cfg->paras)
		{
			const ActCfg *pMore = any_cast<ActCfg>(&v);
			L_COND_V(pMore);
			if (pMore->chgAct)
			{
				vector<any> chgParas = pMore->chgAct(pMore->paras, lv, m_Actor, target);
				pMore->act(chgParas, m_Actor, target);
			}
			else
			{
				pMore->act(pMore->paras, m_Actor, target);
			}
		}
	}
	else if (cfg->chgAct)
	{
		vector<any> chgParas = cfg->chgAct(cfg->paras, lv, m_Actor, target);
		cfg->act(chgParas, m_Actor, target);
	}
	else
	{
		cfg->act(cfg->paras, m_Actor, target);
	}

}

