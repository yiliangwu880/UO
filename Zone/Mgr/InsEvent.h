//实例内事件定义，比如player内事件，monster,npc内事件
#pragma once
#include "svr_util/include/game_util/event_mgr.h"


enum InsEvent
{
	EV_NONE = 0,
	EV_CREATE_DB = 1,
	EV_LOAD_DB = 2,
	EV_SAVE_DB = 3,
	EV_BEFORE_LOGIN = 4, //player别的模块已经加载DB完成。
};

namespace db
{
	class DbPlayer;
}

namespace su
{
	template<>
	struct EventMgrTrait<EV_CREATE_DB> {
		using Fun = void(DbPlayer &data);
	};
	template<>
	struct EventMgrTrait<EV_LOAD_DB> {
		using Fun = void(DbPlayer &data);
	};
	template<>
	struct EventMgrTrait<EV_SAVE_DB> {
		using Fun = void(DbPlayer &data);
	};
	template<>
	struct EventMgrTrait<EV_BEFORE_LOGIN>{
		using Fun = void();
	};
}