#include "Actor.h"

ActorBase::ActorBase(Actor &actor)
	:ActorSubCom<ActorBase>(actor.m_owner, actor)
{
	m_id = CreaeActorId();
	Reg<EV_LOAD_DB>(&ActorBase::OnLoad);
	Reg<EV_SAVE_DB>(&ActorBase::OnSave);

}
void ActorBase::OnLoad(DbPlayer &data)
{
	const DbActorBase &dbBase = data.actor.actorBase;
	m_data     = dbBase;
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
	m_data.str = data.cfg->str;
	m_data.dex = data.cfg->dex;
	m_data.intl = data.cfg->intl;
	m_data.hp = m_data.str;
}

void ActorBase::SetPos(const Point3D &pos)
{
	m_data.x = pos.X;
	m_data.y = pos.Y;
	m_data.z = pos.Z;
}
