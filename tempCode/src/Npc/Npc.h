/*
*/
#pragma once

#include <vector>
#include <map>
#include <functional>
#include "com.h"
#include "cfg.h"

//护送
class Escort : public EventReg
{
public:
	Escort()
	{
		Reg<InsEventId::ChangeXY>(OnChangeXY)
	}
	void ChangeXY()
	{
		if (x,y==target.x,y)
		{
			do escort ok;
		}
	}
};
class Npc : public EventMgr
{
public:
	//int show; 外观
	//Task m_task;提供任务；
	Escort m_Escort;
	Actor m_actor;//战斗生物基本功能
	SceneEntity m_SceneEntity;  //实体场景视野管理

public:
	Npc()
	{
		
	}
private:
};
