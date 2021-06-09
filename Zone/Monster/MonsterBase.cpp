#include "MonsterMgr.h"

MonsterBase::MonsterBase(Monster &owner)
	:MonsterSubCom<MonsterBase>(owner)
{

}

void MonsterBase::Init(const MonsterCfg &cfg)
{
	m_cfg = &cfg;
}
