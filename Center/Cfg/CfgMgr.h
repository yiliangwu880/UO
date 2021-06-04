#pragma once
#include "centerCfg.h"
#include "comCfg.h"

class CfgMgr : public Singleton<CfgMgr>
{
	centerCfg m_centerCfg;
	comCfg m_comCfg;

public:
	const centerCfg &CenterCfg() const { return m_centerCfg; }
	const comCfg &ComCfg() const { return m_comCfg; }
	bool Init();
};

extern const CfgMgr &gCfgMgr;
extern const comCfg::S_testCfg &gTestCfg;

