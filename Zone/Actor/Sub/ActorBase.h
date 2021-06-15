#pragma once
#include "ActorSubCom.h"



class ActorBase : public ActorSubCom<ActorBase>
{
	uint32 m_id = 0; //actor
	string m_name;
	EntityType m_type;
	DbActorBase m_data;


public:
	ActorBase(Actor &actor, EntityType type);
	void InitMonster(const MonsterInit &data);
	Point3D GetPos() const { return Point3D(m_data.x,m_data.y, m_data.z); };
	void SetPos(const Point3D &pos);
	const DbActorBase &GetData() const { return m_data; }


	uint32 GetId() const;//{ return m_id; };
	void SetSceneId(uint32 id)  { m_data.sceneId = id; }
	uint32 GetSceneId() const { return m_data.sceneId; }
	uint16 GetMapId() const;
	CStr &GetName() const;
	EntityType GetType() const { return m_type; };


private:
	void OnCreate(DbActor &data);
	void OnLoad(DbActor &data);
	void OnSave(DbActor &data);

};

struct HairInfo 
{
	static int FakeSerial(Actor &parent);
};

struct FacialHairInfo 
{
	static int FakeSerial(Actor &parent);
};

struct FaceInfo 
{
	static int FakeSerial(Actor &parent);
};