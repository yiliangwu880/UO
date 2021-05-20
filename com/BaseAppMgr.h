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
	using PostFun = std::function<void(void)>;
	vector<PostFun> m_postCb;
public:
	//shell�����������ӣ� 
	//./excute   #��������
	//./excute d #��̨��������
	//./excute stop  #ֹͣ����
	//@argc
	//@argv main ����������
	void Start(int argc, char* argv[], const std::string &app_name);

public:
	virtual bool OnStart() = 0;
	virtual void OnExit() {};
	//��ʱ���ã����һ��timer����
	void AddPost(PostFun cb);

private:
	void OnTimer();

};