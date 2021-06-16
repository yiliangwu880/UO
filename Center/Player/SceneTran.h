#pragma once
#include "CBaseData.h"

class SceneTran : public CPlayerSubCom
{
	enum State
	{
		Playing,       //zone游戏中
		Moving,        //zone切换中
	};
	State m_State = Playing;
public:
	SceneTran(PlayerC &owner)
		:CPlayerSubCom(owner)
	{
	}
	State GetState() const { return m_State; }
	void SetState(State state);

public:
	static void ReqZoneReserve(ZoneSvrCon &con, const proto::ReqZoneReserve &msg);
	static void RspZoneReserve(ZoneSvrCon &con, const proto::RspZoneReserve &msg);
	static void ReqTranZone(ZoneSvrCon &con, const proto::ReqTranZone &msg);
};

