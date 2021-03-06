#pragma once
#include <string>
#include <functional>
#include <limits>
#include <queue>
#include <vector>
#include <unordered_map>
#include <iterator>  
#include <type_traits>
#include <memory>
#include <array>
#include <set>
#include <string.h>
#include <utility>
#include <limits>
#include <cstddef>
#include "log_def.h"
#include "svr_util/include/singleton.h"
#include "svr_util/include/easy_code.h"
#include "svr_util/include/typedef.h"
#include "svr_util/include/cnt_typedef.h"
#include "svr_util/include/stl_boost.h"
#include "svr_util/include/static_reg.h"
#include "svr_util/include/misc.h"
#include "libevent_cpp/include/timer_mgr.h"
#include "Def.h"

#include "GlobalEvent.h"
#include "Mgr/CenterCon.h"
#include "GComCfg.h"
#include "DynCfgMgr.h"
#include "ComMisc.h"

//不区分命名空间
namespace acc
{
}
namespace proto
{
}
namespace db
{
}
using namespace su;
using namespace acc;
using namespace proto;
using namespace std;
using namespace db;

#include "PacketsCom.h"

#define RegCenterMsg(fun) STATIC_RUN(MsgDispatch<CenterCon>::Ins().RegMsgHandler(&fun))
#define RegAccMsg(fun) STATIC_RUN(MsgDispatch<const Session>::Ins().RegMsgHandler(&fun));
//注册全局事件
#define GRegEvent(ev, fun) STATIC_RUN(RegEvent<ev>(&(fun)))