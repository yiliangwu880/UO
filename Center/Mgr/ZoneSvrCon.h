//链接 zone
#pragma once
#include "libevent_cpp/include/include_all.h"
#include "MsgDispatch.h"

class ZoneSvrCon : public lc::SvrCon
{
public:

	template<class ProtoMsg>
	void Send(const ProtoMsg &msg)
	{
		lc::MsgPack msgPack;
		size_t len = sizeof(msgPack.data);
		char *p = msgPack.data;
		L_ASSERT(proto::Pack(msg, p, len));
		msgPack.len = sizeof(msgPack.data) - len;
		SendData(msgPack);
	}
private:
	virtual void OnRecv(const lc::MsgPack &msg) override;
	virtual void OnConnected() override;
};

class Svr : public Singleton<Svr>
{
public:
	lc::Listener<ZoneSvrCon> m_Listener;

public:
};