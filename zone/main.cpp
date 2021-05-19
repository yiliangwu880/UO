
#include "AppMgr.h"
#include "eventMgr.h"
using namespace std;
using namespace su;
using namespace lc;


class AppMgr : public BaseAppMgr
{
public:
	virtual void OnBeforeStart() override
	{
		FireEvent<EV_CFG_INI>();
	}
	virtual void OnStart() override
	{
		FireEvent<EV_START>();
	}
	virtual void OnExit() override
	{
		FireEvent<EV_ON_EXIT>();
	}
};


int main(int argc, char* argv[])
{
	AppMgr app;
	app.Start(argc, argv, "zone");
	return 0;
}

