#pragma once
#include "ActorSubCom.h"



class ActorAttr : public ActorSubCom<ActorAttr>
{
	DbActorAttr m_data;


public:
	ActorAttr(Actor &actor);
	void InitMonster(const MonsterInit &data);
	const DbActorAttr &GetData() const { return m_data; }
	uint32 Hits();
	uint32 HitsMax();
	uint16 Mana();
	uint16 Stam();
	uint16 ManaMax();
	uint16 StamMax();

private:
	void OnCreate(DbActor &data);
	void OnLoad(DbActor &data);
	void OnSave(DbActor &data);

};