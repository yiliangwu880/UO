/*
典型 svr_util libevent_cpp 基础的app管理 写法
*/
#pragma once
#include "game_util/publish_subscribe.h"
#include "singleton.h"
#include "include_all.h"
#include "log_def.h"

//100开始
enum  APP_EVENT
{
	AE_CFG_INI = 1,
	AE_AFTER_NET_INT = 2, //网络管理初始化完
	AE_ON_EXIT = 3, //进程结束
};

namespace su
{
	template<>
	struct EventTraits<AE_CFG_INI> {
		using Fun = void(*)(); //默认事件函数类型，可以不用定义 EventTraits
	};
	template<>
	struct EventTraits<AE_AFTER_NET_INT> {
		using Fun = void(*)();
	};
	template<>
	struct EventTraits<AE_ON_EXIT> {
		using Fun = void(*)();
	};
}

class AppMgr : public Singleton<AppMgr>
{
	bool m_isDaemon = false;

public:
	void Start(int argc, char* argv[], const std::string &app_name);

	void IsDaemon(bool val) { m_isDaemon = val; }
private:
	void OnTimer();

};