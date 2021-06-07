
#pragma once
#include "dbTableDef.h"
#include "ActorOwer.h"
#include "ActorBase.h"
#include "ActorEquip.h"
#include "Observer.h"

enum class ActorType
{
	Player,
	Npc,
	Monster
};


//场景实体,包括人，怪，NPC
class Actor : public Noncopyable, public EventCom<Actor>
{
public:
	ActorOwner &m_owner;
	ActorBase m_ActorBase;
	ActorEquip m_ActorEquip;
	Observer m_Observer;

public:
	Actor(ActorOwner &owner, ActorType t= ActorType::Monster);
	void OnLoad(DbPlayer &dbActor);//player 初始化
	void InitMonster();
	void InitNpc(); 

	void EnterScene(uint32 id);
	void PostDel();//del this
};