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
#include "log_def.h"
#include "svr_util/include/singleton.h"
#include "svr_util/include/easy_code.h"
#include "svr_util/include/typedef.h"
#include "svr_util/include/stl_boost.h"
#include "svr_util/include/static_reg.h"

using namespace su; //不区分su命名空间了
using namespace std;

#define RegCenterMsg(fun) STATIC_RUN(MsgDispatch<CenterCon>::Ins().RegMsgHandler(&(fun));