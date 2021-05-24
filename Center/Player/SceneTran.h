#pragma once
#include "ZoneSvr.h"

class SceneTran : public PlayerSubCom
{
	enum State
	{
		Playing,       //zone游戏中
		Moving,        //zone切换中
	};
	State m_State = Playing;
	uint16 m_zoneId;
	uint32 m_sceneId;
public:
	State State() const { return m_State; }
	void State(State state);

	uint16 ZoneId() const { return m_zoneId; }
	void ZoneId(uint16 val) { m_zoneId = val; }
	uint32 SceneId() const { return m_sceneId; }
	void SceneId(uint32 val) { m_sceneId = val; }
public:
	static void ReqZoneReserve(ZoneSvrCon &con, const proto::ReqZoneReserve &msg);
	static void RspZoneReserve(ZoneSvrCon &con, const proto::RspZoneReserve &msg);
	static void ReqTranZone(ZoneSvrCon &con, const proto::ReqTranZone &msg);
};

