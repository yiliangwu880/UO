// BattleDesign.cpp: 定义应用程序的入口点。
//

#include "unit_test.h"

using namespace std;
UNITTEST(t1)
{
	UNIT_ASSERT(1 ==	1);

	UNIT_INFO("run t1");
}

int main()
{
	UnitTestMgr::Ins().Start();
	
	while (1)
	{
	}
	return 0;
}
