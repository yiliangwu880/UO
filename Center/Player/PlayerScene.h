#pragma once
#include "ZoneSvr.h"

class PlayerScene : public PlayerSubCom
{
	enum State
	{
		WaitEnterZone, //刚登录，等player进入zone
		Playing,       //zone游戏中
		Moving,        //zone切换中
	};
	State m_State = WaitEnterZone;

public:
	State State() const { return m_State; }
	void State(State state);
public:
	static void RspLoginZone_cs(ZoneSvrCon &con, const proto::RspLoginZone_cs &msg);
	static void ReqZoneReserve(ZoneSvrCon &con, const proto::ReqZoneReserve &msg);
	static void RspZoneReserve(ZoneSvrCon &con, const proto::RspZoneReserve &msg);
	static void ReqTranZone(ZoneSvrCon &con, const proto::ReqTranZone &msg);
};

