
#pragma once
#include "dbTableDef.h"
#include "ZoneMisc.h"
#include "SceneMgr.h"
#include "Item/ItemMgr.h"
#include "./State/StateMgr.h"
#include "./Sub/ActorBase.h"
#include "./Sub/ActorEquip.h"
#include "./Sub/Observer.h"
#include "./Sub/ActorSkill.h"
#include "./Sub/ActSkill.h"
#include "./Sub/BuffMgr.h"
#include "./Sub/ActorAttr.h"
#include "./Sub/ActorBag.h"



//场景实体,包括人，怪，NPC
class Actor : public Noncopyable, public EventCom<Actor>
{
public:
	ActorOwner &m_owner;
	ActorBase m_ActorBase;
	ActorAttr m_ActorAttr;
	ActorEquip m_ActorEquip;
	Observer m_Observer;
	StateMgr m_StateMgr;
	BuffMgr m_BuffMgr;
	ActorBag m_ActorBag;

public:
	Actor(ActorOwner &owner, EntityType t= EntityType::Monster);
	void InitMonster(const MonsterInit &data);
	void InitNpc(); 

	void EnterScene(uint32 id);
	bool EnterScene(Scene &scene, uint16 x, uint16 y);
	uint32 GetId() const { return m_ActorBase.GetId(); };
	uint32 Serial() const { return m_ActorBase.GetId(); };
	const string &Name() const;
	bool CanSee(SItem item) { return true; };
	bool CanSee(Actor &actor) { return true; };
};