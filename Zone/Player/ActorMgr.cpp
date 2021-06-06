#include "PlayerMgr.h"


ActorMgr::ActorMgr(Player &owner)
	: PlayerSubCom(owner)
{
	Reg<EV_LOAD_DB>(&ActorMgr::OnLoad);
}

void ActorMgr::OnLoad(DbPlayer &data)
{

}
