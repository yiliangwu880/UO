
#pragma once
#include "MonsterSubCom.h"

//scene 管理actor, actor PostDel来释放
class MonsterBase : public MonsterSubCom<MonsterBase>
{
	
public:
	MonsterBase(Monster &owner);

private:

};
