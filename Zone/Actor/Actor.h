
#pragma once
#include "dbTableDef.h"
#include "ActorOwer.h"
#include "BaseAttr.h"
#include "ActorEquip.h"

enum class ActorType
{
	Player,
	Npc,
	Monster
};


//场景实体,包括人，怪，NPC
class Actor : public Noncopyable
{
public:
	ActorOwner &m_owner;
	BaseAttr m_BaseAttr;
	ActorEquip m_ActorEquip;

public:
	Actor(ActorOwner &owner, ActorType t= ActorType::Monster);
	void Init(const DbActor &dbActor);
	void PostDel();//del this
};