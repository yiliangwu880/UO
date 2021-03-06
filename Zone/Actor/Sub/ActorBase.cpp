#include "Actor.h"
#include "ZoneMisc.h"

ActorBase::ActorBase(Actor &actor, EntityType type)
	:ActorSubCom<ActorBase>(actor.m_owner, actor)
{
	m_id = Serial::NewMobile();
	m_type = type;
	Reg<EV_LOAD_DB>(&ActorBase::OnLoad);
	Reg<EV_SAVE_DB>(&ActorBase::OnSave);
	Reg<EV_CREATE_DB>(&ActorBase::OnCreate);
	Reg<EV_BEFORE_LOGIN_MSG>(&ActorBase::OnBeforeLogin);

}

void ActorBase::OnCreate(DbActor &data)
{
	DbActorBase &dbBase = data.actorBase;
	dbBase.x = 296;//3503;
	dbBase.y = 753; //2578;
	dbBase.z = 14;//14;
	dbBase.body = 400;
	dbBase.hue = 0xffff83ea;
}

void ActorBase::OnLoad(DbActor &data)
{
	const DbActorBase &dbBase = data.actorBase;
	m_data     = dbBase;
	m_name = dbBase.name;
	//L_DEBUG("pos =%d %d", dbBase.x, dbBase.y);
}

void ActorBase::OnSave(DbActor &data)
{
	DbActorBase &dbBase = data.actorBase;
	dbBase = m_data;
}


void ActorBase::OnBeforeLogin()
{

}

void ActorBase::InitMonster(const MonsterInit &data)
{

}

void ActorBase::SetPos(const Point3D &pos)
{
	m_data.x = pos.X;
	m_data.y = pos.Y;
	m_data.z = pos.Z;
}

uint32 ActorBase::GetId() const
{	
	return m_id; 
}

uint16 ActorBase::GetMapId() const
{
	SceneId id;
	id.id = m_data.sceneId;
	return id.mapId;
}

su::CStr & ActorBase::GetName() const
{
	return m_name;
}


int FaceInfo::FakeSerial(Actor &parent)
{
	return (0x7FFFFFFF - 0x400 - 2 - (parent.Serial() * 4));
}

int FacialHairInfo::FakeSerial(Actor &parent)
{
	return (0x7FFFFFFF - 0x400 - 1 - (parent.Serial() * 4));
}

int HairInfo::FakeSerial(Actor &parent)
{
	return (0x7FFFFFFF - 0x400 - (parent.Serial() * 4));
}
