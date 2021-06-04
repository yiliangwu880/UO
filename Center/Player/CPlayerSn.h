#pragma once
#include "CBaseData.h"

class CPlayerSn : public CPlayerSubCom
{
	acc::SessionId m_sid;

public:
	CPlayerSn(CPlayer &owner)
		:CPlayerSubCom(owner)
	{
	}

	const acc::SessionId &GetSid() const { return m_sid; }
	void SetSid(acc::SessionId val) { m_sid = val; }
};


