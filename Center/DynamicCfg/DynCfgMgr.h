//类json配置，方便修改后不用编译。
#pragma once
#include "centerCfg.h"
#include "comCfg.h"

class DynCfgMgr : public Singleton<DynCfgMgr>
{
	centerCfg m_centerCfg;
	comCfg m_comCfg;

public:
	const centerCfg &CenterCfg() const { return m_centerCfg; }
	const comCfg &ComCfg() const { return m_comCfg; }
	bool Init();
};

extern const DynCfgMgr &gDynCfg;
extern const comCfg::S_testCfg &gTestCfg;

