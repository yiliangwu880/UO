//全局事件定义
#pragma once

#include "game_util/publish_subscribe.h"
#include "svr_util/include/static_reg.h"

enum Event
{
	EV_SVR_CFG_INI = 1,
	EV_SVR_START = 2,
	EV_SVR_EXIT = 3, //进程结束
	EV_FINISH_WORLD_SCENE = 4, //初始化完世界场景
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
