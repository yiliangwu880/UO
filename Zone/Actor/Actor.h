
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

class NetState;
class Packet;
class Player;

//暂时不分模块，杂项数据
struct ActorMiscData 
{
	time_t NextActionTime = 0;
	time_t m_NextActionMessage = 0;
	bool m_Warmode = false;
};
//场景实体,包括人，怪，NPC
class Actor : public Noncopyable, public EventCom<Actor>, public WeakPtr<Actor>
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
	ActorSkill m_ActorSkill;
	ActorMiscData m_ActorMiscData;

public:
	static const int BodyWeight=14; 
	static const int ActionDelay = 500;

public:
	Actor(ActorOwner &owner, EntityType t= EntityType::Monster);
	~Actor();
	void InitMonster(const MonsterInit &data);
	void InitNpc(); 

	void EnterScene(uint32 id);
	bool EnterScene(Scene &scene, uint16 x, uint16 y);
	uint32 GetId() const { return m_ActorBase.GetId(); };
	uint32 Serial() const { return m_ActorBase.GetId(); };
	const string &Name() const;
	bool CanSee(SItem item) { return true; };
	bool CanSee(Actor &actor) { return true; };

	::NetState *NetState();
	void Send(Packet &packet);

	//@from 请求者
	void OnStatsQuery(Actor &from);
	void OnSkillsQuery(Actor &from);

	bool CanBeRenamedBy(Actor &from) { return false; }
	uint32 Hits() { return m_ActorAttr.Hits(); };
	uint32 HitsMax() { return m_ActorAttr.HitsMax(); };
	uint32 Mana() { return m_ActorAttr.Mana(); };
	uint32 Stam() { return m_ActorAttr.Stam(); };
	uint32 ManaMax() { return m_ActorAttr.ManaMax(); };
	uint32 StamMax() { return m_ActorAttr.StamMax(); };
	uint32 Str() { return m_ActorAttr.GetData().str; };
	uint32 Dex() {return m_ActorAttr.GetData().dex; };
	uint32 Int() {return m_ActorAttr.GetData().intl; };
	uint32 TotalGold() { return 100; }
	uint32 PhysicalResistance() { return 70; }
	uint32 FireResistance() { return 70; }
	uint32 ColdResistance() { return 70; }
	uint32 PoisonResistance() { return 70; }
	uint32 EnergyResistance() { return 70; }
	uint32 Luck() { return 10; }


	uint32 TotalWeight() { return 1; }
	uint32 MaxWeight() { return 1000; }
	bool Female() { return m_ActorBase.GetData().female; }
	uint32 RaceID() { return m_ActorBase.GetData().race; }
	//真实三围总数上限
	uint32 StatCap() { return 225; }
	uint32 FollowersMax() { return 5; }
	uint32 Followers() { return 0; }
	uint32 TithingPoints() { return 10; }
	IWeapon *Weapon();
	int GetAOSStatus(int index);
	int GetMaxResistance(ResistanceType type);

	StatLockType StrLock();
	StatLockType DexLock();
	StatLockType IntLock();
	Player *GetPlayer();
	bool IsStaff();
	time_t &NextActionTime(); //下次可 action ms

	void SendActionMessage();
	void SendLocalizedMessage(int number);
	void OnPaperdollRequest();
	void DisplayPaperdollTo(Actor &from);
	bool CanPaperdollBeOpenedBy(Actor &from);
	bool Warmode() { return m_ActorMiscData.m_Warmode; }
	bool AllowEquipFrom(Actor &from);
	::AccessLevel AccessLevel();
	bool ViewOPL() { return true; }
};
using WActor = std::weak_ptr<Actor>;
using SActor = std::shared_ptr<Actor>;
using Mobile = Actor;