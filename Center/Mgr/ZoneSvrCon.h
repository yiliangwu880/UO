//链接 zone
#pragma once
#include "libevent_cpp/include/include_all.h"
#include "MsgDispatch.h"

class ZoneSvrCon : public lc::SvrCon, public WeakPtr<ZoneSvrCon>
{
	uint16 m_svrId = 0;

public:
	~ZoneSvrCon();
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
	void Init(uint16 svrId) { m_svrId = svrId; };
	uint16 GetSvrId() { return m_svrId; }
private:
	virtual void OnRecv(const lc::MsgPack &msg) override;
	virtual void OnConnected() override;
};

