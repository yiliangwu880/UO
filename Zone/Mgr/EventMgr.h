#pragma once

#include "game_util/publish_subscribe.h"
#include "svr_util/include/static_reg.h"

//100开始
enum Event
{
	EV_CFG_INI = 1,
	EV_START = 2, 
	EV_ON_EXIT = 3, //进程结束
};

namespace su
{
	template<>
	struct EventTraits<EV_CFG_INI> {
		using Fun = void(*)(bool &);
	};
	template<>
	struct EventTraits<EV_START> {
		using Fun = void(*)(bool &);
	};

}
