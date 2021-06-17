
#include "ComMisc.h"
#include "svr_util/include/time/su_timestamp.h"

bool gTrue = true;
long Core::TickCount()
{
	return su::SysTime::Ins().Ms();
}
