#include "GCfg.h"

ActCfgMgr::ActCfgMgr()
	:m_ActCfg({
			//{1, { 1, Act::Act1, ChgAct::Lv0 }},
			{2, { 2, Act::EarthQuake, ChgAct::Lv0, /*技能伤害系数*/{100, 1, "abc"} }},
			//{1, { 1 }},
		})
{}

GRegEvent(EV_SVR_CFG_INI, ActCfgMgr::CheckCfg)
void ActCfgMgr::CheckCfg(bool &ret)
{
	for (const auto &v : gCfg.m_ActCfgMgr.m_ActCfg)
	{
		const ActCfg &cfg = v.second;
		const auto it = Act2Check::Ins().find(cfg.act);
		if (it == Act2Check::Ins().end())
		{
			L_ERROR("ActCfg[%d] no check fun. ", cfg.id);
			ret = false;
		}
		CheckActFun &checkFun =  it->second;
		bool r = checkFun(cfg.paras);
		if (!r)
		{
			L_ERROR("ActCfg[%d] check paras fail. ", cfg.id);
			ret = false;
		}
	}

}

