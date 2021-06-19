#include "Actor.h"

ActorSkill::ActorSkill(Actor &actor)
	:ActorSubCom<ActorSkill>(actor.m_owner, actor)
{
	Reg<EV_CREATE_DB>(&ActorSkill::OnCreate);
	Reg<EV_LOAD_DB>(&ActorSkill::OnLoad);
}

void ActorSkill::OnCreate(DbActor &data)
{
	data.skills.vecSkill.clear();
	for (uint32 i = 0; i < m_all.size(); ++i)
	{
		DbSkill dbSkill;
		dbSkill.idx = i;
		data.skills.vecSkill.push_back(dbSkill);
	}
	OnLoad(data);
}

void ActorSkill::OnLoad(DbActor &data)
{
	m_DbSkills = &data.skills;
	L_COND_V(m_DbSkills->vecSkill.size() == m_all.size());
	for (uint32 i = 0; i < m_all.size(); ++i)
	{
		m_all[i].Init(&(m_DbSkills->vecSkill[i]));
	}
}

Skill * ActorSkill::GetSkill(uint32 idx)
{
	if (idx >= m_all.size())
	{
		return nullptr;
	}
	return &m_all[idx];
}

void Skill::Init(DbSkill *dbSkill)
{
	L_COND_V(dbSkill);
	m_DbSkill = dbSkill;
	m_SkillCfg = gCfg.GetSkillCfg(m_DbSkill->idx);
	L_COND_V(m_SkillCfg);
}

SkillLock Skill::Lock()
{
	L_COND(m_DbSkill->lock >= 0 && m_DbSkill->lock <= 2, SkillLock::Up);
	return (SkillLock)m_DbSkill->lock;
}

const SkillCfg * Skill::GetCfg()
{
	L_COND(m_SkillCfg, nullptr);
	return m_SkillCfg;
}

