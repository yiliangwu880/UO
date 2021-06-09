#pragma once
#include "Act.h"


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
};