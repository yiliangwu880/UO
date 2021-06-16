#pragma once
#include "ComMisc.h"

using CPlayerSubCom = SubCom<PlayerC>;
struct BaseData : public CPlayerSubCom
{
	uint64 m_uin = 0;
	uint16 m_zoneId = ZONE_GROUP_ID;
	uint32 m_sceneId = 0;
	string name;

	BaseData(PlayerC &owner)
		:CPlayerSubCom(owner)
	{

	}

};


