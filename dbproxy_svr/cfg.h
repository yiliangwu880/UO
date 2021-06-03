/*
 管理连接db客户端
*/

#pragma once
#include "base_include.h"
#include "Cfg/Cfg.h"
#include "Cfg/comCfg.h"

class CfgMgr : public Singleton<CfgMgr>
{
public:
	bool Init();
	const comCfg &GetCfg() const { return m_comCfg; }

private:
	comCfg m_comCfg;
};