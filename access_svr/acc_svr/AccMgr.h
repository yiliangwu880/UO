#pragma once
#include <unordered_map>
#include <queue>
#include "log_def.h"
#include "libevent_cpp/include/include_all.h"
#include "svr_util/include/su_include.h"
#include "svr_util/include/time/su_timer.h"
#include "../acc_proto/include/proto.h"

class AccSeting : public Singleton<AccSeting>
{
public:
	acc:: MsgAccSeting m_seting;
	std::unordered_map<uint16, uint16> m_cmd2GrpId; //来源 MsgAccSeting::vecCmd2GrupId
};

extern AccSeting *g_AccSeting; //AccSeting::Ins()的便捷方式

