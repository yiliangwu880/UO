#pragma once
#include "Act.h"
#include "svr_util/include/static_reg.h"

//单例， 记录每个 ActFun 函数的配置参数合法函数。启服时检测。
REG_MAP_NAME_DECLARE(Act2Check, ActFun, CheckActFun);

struct ActCfg
{
	uint16 id;
	ActFun act;
	ChgActParaFun chgAct;
	vector<any> paras;
};

struct ActCfgMgr 
{
	unordered_map<uint16, ActCfg> m_ActCfg;

	ActCfgMgr();
	
	static void CheckCfg(bool &ret);
};