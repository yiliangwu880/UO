/*
典型 svr_util libevent_cpp 基础的app管理 写法
项目 https://github.com/yiliangwu880/UO.git 也有，以UO项目为准。这里是旧参考

*/
#pragma once
#include "singleton.h"
#include "include_all.h"
#include "log_def.h"

class BaseAppMgr 
{
public:
	//shell启动命令例子： 
	//./excute   #启动进程
	//./excute d #后台启动进程
	//./excute stop  #停止进程
	//@argc
	//@argv main 函数参数。
	void Start(int argc, char* argv[], const std::string &app_name);

public:
	virtual void OnBeforeStart()=0;
	virtual void OnStart() = 0;
	virtual void OnExit() {};

private:
	void OnTimer();

};