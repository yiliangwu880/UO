#include "BaseAppMgr.h"
#include "GlobalEvent.h"

using namespace std;
using namespace su;
using namespace lc;

class AppMgr : public BaseAppMgr, public Singleton<AppMgr>
{
public:
	virtual bool OnStart() override
	{
		bool ret = true;
		FireEvent<EV_SVR_CFG_INI>(ret); //任意事件改为ret == false,执行失败
		L_COND(ret, false);
		FireEvent<EV_SVR_START>(ret);
		L_COND(ret, false);

		return true;
	}
	virtual void OnExit() override
	{
		FireEvent<EV_SVR_EXIT>();
	}
};