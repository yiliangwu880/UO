/*
���� svr_util libevent_cpp ������app���� д��
��Ŀ https://github.com/yiliangwu880/UO.git Ҳ�У���UO��ĿΪ׼�������Ǿɲο�

*/
#pragma once
#include "singleton.h"
#include "include_all.h"
#include "log_def.h"

class BaseAppMgr 
{
public:
	//shell�����������ӣ� 
	//./excute   #��������
	//./excute d #��̨��������
	//./excute stop  #ֹͣ����
	//@argc
	//@argv main ����������
	void Start(int argc, char* argv[], const std::string &app_name);

public:
	virtual void OnBeforeStart()=0;
	virtual void OnStart() = 0;
	virtual void OnExit() {};

private:
	void OnTimer();

};