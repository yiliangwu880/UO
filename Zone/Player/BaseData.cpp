#include "PlayerMgr.h"


BaseData::BaseData(Player &owner)
	: PlayerSubCom(owner)
	, EventCom<BaseData>(owner)
{}
