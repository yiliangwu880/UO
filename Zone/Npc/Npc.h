/*
*/
#pragma once
#include "Actor/Actor.h"

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
public:
	//int show; 外观
	//Task m_task;提供任务；
	Escort m_Escort;
	Actor m_actor;//战斗生物基本功能
public:
	virtual void PostDel() override;

public:
	Npc();

private:
};
