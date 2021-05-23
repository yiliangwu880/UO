#pragma once

class PlayerScene : public PlayerSubCom
{
	enum State
	{
		WaitTranIn,		//预定空位状态，等转换player进入
		Playing,       //zone游戏中
		WaitReserve,   //等预定转换zone结果
	};
	State m_State = Playing;

public:
	State State() const { return m_State; }
	bool TranZone(uint16 zoneId, uint32 sceneId);

public:
	static void ReqZoneReserve(ZoneSvrCon &con, const proto::ReqZoneReserve &msg);
	static void ReqTranZone(ZoneSvrCon &con, const proto::ReqTranZone &msg);

};

