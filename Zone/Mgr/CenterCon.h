//链接center
#pragma once

#include "libevent_cpp/include/include_all.h"
#include "ProtoInclude.h"

class CenterCon : public lc::ClientCon, public Singleton<CenterCon>
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
		L_DEBUG("send len =%d", msgPack.len);
		SendData(msgPack);
	}
private:
	virtual void OnRecv(const lc::MsgPack &msg) override;
	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
};
