#include "ZoneMisc.h"
#include "ActorMgr.h"

Actor * World::FindMobile(uint32 id)
{
	return ActorMgr::Ins().Find(id);
}

SItem World::FindItem(uint32 id)
{
	return ItemMgr::Ins().Find(id);
}

IEntity * World::FindEntity(uint32 id)
{
	Serial serial(id);
	if (serial.IsItem())
	{
		SItem item = FindItem(serial);
		if (item == nullptr)
		{
			return nullptr;
		}
		return item.get();
	}
	else if (serial.IsMobile())
	{
		return FindMobile(serial);
	}

	return nullptr;
}

ActorOwner::ActorOwner(DbActor &dbActor)
	:m_DbActor(dbActor)
{

}

ActorOwner::~ActorOwner()
{
	
}


std::string Titles::ComputeTitle(Actor &beholder, Actor &beheld)
{
	return "abc";
}
