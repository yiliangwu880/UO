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
	uint32 Mana();
	uint32 Stam();
	uint32 ManaMax();
	uint32 StamMax();

private:
	void OnCreate(DbActor &data);
	void OnLoad(DbActor &data);
	void OnSave(DbActor &data);

};