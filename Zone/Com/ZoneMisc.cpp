#include "ZoneMisc.h"
#include "ActorMgr.h"

Actor * World::FindMobile(uint32 id)
{
	return ActorMgr::Ins().Find(id);
}
