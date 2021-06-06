#pragma once
#include "svr_util/include/game_util/event_mgr.h"

class ActorOwner : public EventMgr, public Noncopyable
{
public:
	virtual ~ActorOwner() {}
	virtual void PostDel() {}; //del this
};