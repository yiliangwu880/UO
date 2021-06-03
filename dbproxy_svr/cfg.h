/*
 管理连接db客户端
*/

#pragma once
#include "base_include.h"
#include "Cfg/comCfg.h"

class CfgMgr : public Singleton<CfgMgr>
{
public:
	comCfg m_comCfg;

public:
	bool Init();

};