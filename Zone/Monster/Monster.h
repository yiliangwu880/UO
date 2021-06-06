/*
不同怪物用组合表达，避免继承层次太多导致的复杂性 。
*/
#pragma once
#include "Actor/Actor.h"
//scene 管理actor, actor PostDel来释放
class Monster : public WeakPtr<Monster>, public ActorOwner
{
public:
	//int show; 外观
	//Drop dropCfg;
	Actor m_actor;//战斗生物基本功能

public:
	virtual void PostDel() override;
public:
	Monster();

	//某个函数，从位置触发，动作影响别的生物类型
	//void  PosAction()
	//{
	//	int x, y;
	//	get all SceneEntity;
	//	for (SceneEntity &v: all)
	//	{
	//		Actor actor = v.getActor;
	//		do(m_actor, actor);
	//	}
	//}

private:
};