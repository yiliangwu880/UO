/*
*/
#pragma once

#include <vector>
#include <map>
#include <functional>
#include "com.h"
#include "cfg.h"

//����
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
	//int show; ���
	//Task m_task;�ṩ����
	Escort m_Escort;
	Actor m_actor;//ս�������������
	SceneEntity m_SceneEntity;  //ʵ�峡����Ұ����

public:
	Npc()
	{
		
	}
private:
};
