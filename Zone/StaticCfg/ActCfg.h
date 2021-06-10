#pragma once
#include "Act.h"
#include "svr_util/include/static_reg.h"



struct ActCfg
{
	ActFun act;
	vector<any> paras;
	ChgActParaFun chgAct;
};

struct ActCfgMgr 
{
	unordered_map<uint16, ActCfg> m_ActCfg;

	ActCfgMgr();
	
	static void CheckCfg(bool &ret);
};