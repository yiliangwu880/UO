/*
不同怪物用组合表达，避免继承层次太多导致的复杂性 。
*/
#pragma once
#include "Actor/Actor.h"
#include "Ai/Ai.h"
#include "MonsterBase.h"
#include "SceneMgr.h"


//scene 管理actor, actor PostDel来释放
class Monster : public WeakPtr<Monster>, public ActorOwner
{
	uint32 m_uin;
public:
	Actor m_Actor;//战斗生物基本功能, 必须放第一，这样 m_ai 才能正确引用
	Ai m_ai; 
	MonsterBase m_MonsterBase;

public:
	void Init(const MonsterInit &data);

public:
	Monster(uint32 uin);


	//某个函数，从位置触发，动作影响别的生物类型
	//void  PosAction()
	//{
	//	int x, y;
	//	get all SceneEntity;
	//	for (SceneEntity &v: all)
	//	{
	//		Actor actor = v.getActor;
	//		do(m_Actor, actor);
	//	}
	//}

private:
};
