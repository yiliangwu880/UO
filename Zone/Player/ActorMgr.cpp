#include "PlayerMgr.h"


ActorMgr::ActorMgr(Player &owner)
	: PlayerSubCom(owner)
	//, m_actor(owner)
{
	Reg<EV_LOAD_DB>(&ActorMgr::OnLoad);
}

void ActorMgr::OnLoad(DbPlayer &data)
{
//	m_actor.Init(data.actor);
}