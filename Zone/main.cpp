#include "AppMgr.h"
#include "EventMgr.h"
using namespace std;
using namespace su;
using namespace lc;




int main(int argc, char* argv[])
{
	AppMgr::Ins().Start(argc, argv, "zone");
	return 0;
}

