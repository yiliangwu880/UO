#include "MonsterMgr.h"

MonsterBase::MonsterBase(Monster &owner)
	:MonsterSubCom<MonsterBase>(owner)
{

}
