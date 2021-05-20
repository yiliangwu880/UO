//链接center
#pragma once
#include "libevent_cpp/include/include_all.h"
#include "MsgDispatch.h"

class ZoneSvrCon : public lc::SvrCon
{
public:

	template<class Msg>
	bool SendMsg(const Msg &msg)
	{
		lc::MsgPack msgPack;
		size_t len = sizeof(msgPack.data);
		char *p = msgPack.data;
		L_ASSERT(proto::Pack(msg, p, len));
		return SendData(msgPack);
	}
private:
	virtual void OnRecv(const lc::MsgPack &msg) override;
	virtual void OnConnected() override;
};

class ZoneSvr : public Singleton<ZoneSvr>
{
public:
	lc::Listener<ZoneSvrCon> m_Listener;

public:
};