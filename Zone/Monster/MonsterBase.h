
#pragma once
#include "MonsterSubCom.h"
#include "GCfg.h"

//scene 管理actor, actor PostDel来释放
class MonsterBase : public MonsterSubCom<MonsterBase>
{
	const MonsterCfg *m_cfg = nullptr;

public:
	MonsterBase(Monster &owner);
	void Init(const MonsterCfg &cfg);
private:

};
