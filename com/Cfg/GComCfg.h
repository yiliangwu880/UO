//全局游戏静态配置
#pragma once
#include "MiscCfg.h"

//game cfg
class GComCfg : public Singleton<GComCfg>
{
	MiscCfg m_MiscCfg;

public:
	const MiscCfg &GetMiscCfg()const { return m_MiscCfg; }
};
extern const GComCfg &gComCfg;

