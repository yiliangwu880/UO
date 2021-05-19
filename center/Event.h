#pragma once

#include "game_util/publish_subscribe.h"
//100开始
enum Event
{
	EV_CFG_INI = 1,
	EV_START = 2, 
	EV_ON_EXIT = 3, //进程结束
};

namespace su
{
	//template<>
	//struct EventTraits<Event::CFG_INI> {
	//	using Fun = void(*)(); //默认事件函数类型，可以不用定义 EventTraits
	//};

}
