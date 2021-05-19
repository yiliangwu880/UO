#include "libevent_cpp/include/include_all.h"
#include "svr_util/include/su_mgr.h"
#include "svr_util/include/single_progress.h"
#include "svr_util/include/log_file.h"
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
	app.Start(argc, argv, "center");
	return 0;
}

