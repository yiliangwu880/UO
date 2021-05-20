//Á´½Ócenter
#pragma once
#include "libevent_cpp/include/include_all.h"
#include "MsgDispatch.h"

class ZoneSvrCon : public lc::SvrCon
{
public:


private:
	virtual void OnRecv(const lc::MsgPack &msg) override;
	virtual void OnConnected() override;
};

