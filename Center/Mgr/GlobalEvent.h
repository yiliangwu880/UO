#pragma once

#include "game_util/publish_subscribe.h"
#include "svr_util/include/static_reg.h"

enum Event
{
	EV_SVR_CFG_INI = 1,
	EV_SVR_START = 2, 
	EV_SVR_EXIT = 3, //进程结束
};

namespace su
{
	template<>
	struct EventTraits<EV_SVR_CFG_INI> {
		using Fun = void(*)(bool &);
	};
	template<>
	struct EventTraits<EV_SVR_START> {
		using Fun = void(*)(bool &);
	};

}
