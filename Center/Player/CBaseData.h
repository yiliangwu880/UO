#pragma once
#include "ZoneSvr.h"
#include "CAccMgr.h"
#include "SceneTran.h"
#include "LoginPlayer.h"


struct BaseData : public CPlayerSubCom
{
	uint64 m_uin = 0;
	uint16 m_zoneId = 0;
	uint32 m_sceneId = 0;
	string name;

	BaseData(CPlayer &owner);
};


