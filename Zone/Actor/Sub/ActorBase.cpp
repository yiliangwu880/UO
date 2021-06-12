#include "Actor.h"

ActorBase::ActorBase(Actor &actor)
	:ActorSubCom<ActorBase>(actor.m_owner, actor)
{
	m_id = CreaeActorId();
	Reg<EV_LOAD_DB>(&ActorBase::OnLoad);
	Reg<EV_SAVE_DB>(&ActorBase::OnSave);
	Reg<EV_CREATE_DB>(&ActorBase::OnCreate);

}

void ActorBase::OnCreate(DbPlayer &data)
{
	DbActorBase &dbBase = data.actor.actorBase;
	dbBase.x = 3503;
	dbBase.y = 2578;
	dbBase.z = 14;
	dbBase.body = 400;
	dbBase.hue = 0x000083ea;
}

void ActorBase::OnLoad(DbPlayer &data)
{
	const DbActorBase &dbBase = data.actor.actorBase;
	m_data     = dbBase;
	m_name = data.name;
}

void ActorBase::OnSave(DbPlayer &data)
{
	DbActorBase &dbBase = data.actor.actorBase;
	dbBase = m_data;
}


uint32 ActorBase::CreaeActorId()
{
// uint32 可以存放, 假设秒一个id
//4,294,967,295 sec
//= 49,710 天
// = 136年

	static uint32 idSeed = 0;
	idSeed++;
	return idSeed;
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

