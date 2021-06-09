
#pragma once
#include "dbTableDef.h"
#include "ZoneMisc.h"
#include "ActorBase.h"
#include "ActorEquip.h"
#include "Observer.h"
#include "SceneMgr.h"




//场景实体,包括人，怪，NPC
class Actor : public Noncopyable, public EventCom<Actor>
{
public:
	ActorOwner &m_owner;
	ActorBase m_ActorBase;
	ActorEquip m_ActorEquip;
	Observer m_Observer;

public:
	Actor(ActorOwner &owner, EntityType t= EntityType::Monster);
	void OnLoad(DbPlayer &dbActor);//player 初始化
	void InitMonster(const MonsterInit &data);
	void InitNpc(); 

	void EnterScene(uint32 id);
	bool EnterScene(Scene &scene, uint16 x, uint16 y);
};