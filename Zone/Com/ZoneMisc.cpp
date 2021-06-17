#include "ZoneMisc.h"
#include "ActorMgr.h"

Actor * World::FindMobile(uint32 id)
{
	return ActorMgr::Ins().Find(id);
}

ActorOwner::~ActorOwner()
{
	
}


std::string Titles::ComputeTitle(Actor &beholder, Actor &beheld)
{
	return "abc";
}
