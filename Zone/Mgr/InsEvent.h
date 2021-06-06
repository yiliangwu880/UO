//实例内事件定义，比如player内事件，monster,npc内事件
#pragma once
#include "svr_util/include/game_util/event_mgr.h"


enum InsEvent
{
	EV_NONE = 0,
	EV_LOAD_DB = 1,
	EV_SAVE_DB = 2,
};

namespace db
{
	class DbPlayer;
}

namespace su
{
	template<>
	struct EventMgrTrait<EV_LOAD_DB> {
		using Fun = void(DbPlayer &data);
	};
	template<>
	struct EventMgrTrait<EV_SAVE_DB> {
		using Fun = void(DbPlayer &data);
	};
}