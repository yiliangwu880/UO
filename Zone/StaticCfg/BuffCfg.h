#pragma once
#include "Actor/State/StateDef.h"

enum class BuffId
{
	None,
	TriggerXixue,
	TargetXixue,

};

struct BuffState 
{
	StateId id;
	vector<any> paras; //id为 StateId::More时，每个元素为 BuffState
};

struct BuffCfg
{
	uint16 sec;
	BuffState state;
};

struct BuffCfgMgr
{
	unordered_map<uint16, BuffCfg> m_BuffCfg;

	BuffCfgMgr();
	
	static void CheckCfg(bool &ret);
};