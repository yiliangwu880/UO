//实例内事件定义，比如player内事件，monster,npc内事件
#pragma once
#include "svr_util/include/game_util/event_mgr.h"


enum InsEvent
{
	EV_NONE = 0,
	//存库的actor create, load， save。 player或者宠物
	EV_CREATE_DB = 1, 
	EV_LOAD_DB = 2,
	EV_SAVE_DB = 3,

	EV_AFTER_INIT_DbActor = 4, //不能存库的npc monster 初始化DbActor后，触发事件初始化各个actor模块
	EV_BEFORE_LOGIN_MSG = 7, //player别的模块已经加载DB完成。 再发登录消息给客户端前触发
};

namespace db
{
	struct DbPlayer;
	struct DbActor;
}

namespace su
{


	template<>
	struct EventMgrTrait<EV_CREATE_DB> {
		using Fun = void(DbActor &data);
	};
	template<>
	struct EventMgrTrait<EV_LOAD_DB> {
		using Fun = void(DbActor &data);
	};
	template<>
	struct EventMgrTrait<EV_SAVE_DB> {
		using Fun = void(DbActor &data);
	};
	template<>
	struct EventMgrTrait<EV_AFTER_INIT_DbActor> {
		using Fun = void(DbActor &data);
	};

}