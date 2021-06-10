#pragma once
#include "ActorSubCom.h"



class BaseState
{
public:
	virtual ~BaseState() {};
	virtual void Init(const vector<any> &cfg) {};
	//已经有该状态，再加一次就是重加, 默认不能重加
	virtual void RetAdd(const vector<any> &cfg) {};
};





