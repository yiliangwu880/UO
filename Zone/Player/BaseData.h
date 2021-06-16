#pragma once
#include "ComMisc.h"
#include "SubCom.h"


class BaseData : public PlayerSubCom<BaseData>
{
public:
	uint64 m_uin = 0;
	string name;
public:
	BaseData(Player &owner);
};

