#pragma once
#include "BaseData.h"

class SceneTran : public PlayerSubCom
{
	enum State
	{
		WaitTranIn,		//预定空位状态，等转换player进入
		Playing,       //zone游戏中
		WaitReserve,   //等预定转换zone结果
		WaitDel,		//传送走了，等删除
	};
	State m_State = Playing;

	//WaitReserve 的情况，都为true表示 acc缓存, center 预定都ok
	bool m_isAccCacheOk = false;
	bool m_isReserveOk = false;
public:
	SceneTran(Player &owner)
		:PlayerSubCom(owner)
	{}
	bool TranZone(uint16 zoneId, uint32 sceneId);
	void CheckReserve();
	void OnMsgRspCacheMsg(bool isCache);

public:
	static void ReqZoneReserve(CenterCon &con, const proto::ReqZoneReserve &msg);
	static void ReqTranZone(CenterCon &con, const proto::ReqTranZone &msg);
	static void RspZoneReserve(CenterCon &con, const proto::RspZoneReserve &msg);

};

