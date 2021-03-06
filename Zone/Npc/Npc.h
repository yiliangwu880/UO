/*
*/
#pragma once
#include "Actor/Actor.h"
#include "Ai/Ai.h"
#include "SceneMgr.h"

//护送
class Escort //: public EventReg
{
public:
	//Escort()
	//{
	//	Reg<InsEventId::ChangeXY>(OnChangeXY)
	//}
	//void ChangeXY()
	//{
	//	if (x,y==target.x,y)
	//	{
	//		do escort ok;
	//	}
	//}
};

//scene 管理actor, actor PostDel来释放
class Npc : public WeakPtr<Npc>, public ActorOwner
{
	uint32 m_id;
	DbActor m_DbActor;
public:
	Actor m_Actor;//战斗生物基本功能, 必须放第一，这样 m_ai 才能正确引用
	Ai m_ai;
	//int show; 外观
	//Task m_task;提供任务；
	Escort m_Escort;
public:

public:
	Npc(uint32 id);

private:
};
