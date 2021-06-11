#pragma once
#include "ActorSubCom.h"



class ActorBase : public ActorSubCom<ActorBase>
{
	uint32 m_id = 0; //actor
	string m_name;
	DbActorBase m_data;


public:
	ActorBase(Actor &actor);
	void InitMonster(const MonsterInit &data);
	Point3D GetPos() const { return Point3D(m_data.x,m_data.y, m_data.z); };
	void SetPos(const Point3D &pos);
	const DbActorBase &GetData() const { return m_data; }
	uint32 GetId() const { return m_id; };
	void SetSceneId(uint32 id)  { m_data.sceneId = id; }
	uint32 GetSceneId() const { return m_data.sceneId; }
	uint16 GetMapId() const;
	CStr &GetName() const;
	uint32 Hits();
	uint32 HitsMax();
	uint16 Mana();
	uint16 Stam();
	uint16 ManaMax();
	uint16 StamMax();

private:
	void OnCreate(DbPlayer &data);
	void OnLoad(DbPlayer &data);
	void OnSave(DbPlayer &data);

	static uint32 CreaeActorId();
};