// BattleDesign.cpp: 定义应用程序的入口点。
//

#include "unit_test.h"
#include "battle/com.h"
#include <functional>
#include <memory>



class Share  : public BaseWeak<Share>
{
public:

};

namespace
{
	weak_ptr<Share> wp;
	void f1()
	{
		Share a;
		wp = a.WeakPtr();
		auto p = wp.lock();
		UNIT_ASSERT(p);
	}

}

UNITTEST(share)
{
	f1();
	{
		auto p = wp.lock();
		UNIT_ASSERT(!p);
		UNIT_INFO("p == null");
	}

}
