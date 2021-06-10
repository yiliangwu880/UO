#include "GCfg.h"

using namespace Act;

using VecActCfg = vector<ActCfg>;

ActCfgMgr::ActCfgMgr()
	:m_ActCfg({
			{2, {  EarthQuake, /*技能伤害系数*/{100, 1, "abc"}, /*配置参数调整方案*/ChgAct::Lv0 }},
			//多个act 组合
			{3, {  More, { ActCfg{Act1}, ActCfg{Act2,{1,2}, ChgAct::Lv0} }  }},
		})
{}

GRegEvent(EV_SVR_CFG_INI, ActCfgMgr::CheckCfg)
void ActCfgMgr::CheckCfg(bool &ret)
{
	for (const auto &v : gCfg.m_ActCfgMgr.m_ActCfg)
	{
		const ActCfg &cfg = v.second;
		if (cfg.act == nullptr)
		{
			L_ERROR("ActCfg[%d] no Act fun. ", v.first);
			ret = false;
		}
	}

	for (const auto &v : gCfg.m_ActCfgMgr.m_ActCfg)
	{
		const ActCfg &cfg = v.second;
		const auto it = Act2Check::Ins().find(cfg.act);
		if (it == Act2Check::Ins().end())
		{//no check function
			continue;
		}
		CheckActFun &checkFun = it->second;
		bool r = checkFun(cfg.paras);
		if (!r)
		{
			L_ERROR("ActCfg[%d] check paras fail. ", v.first);
			ret = false;
		}
	}

}

