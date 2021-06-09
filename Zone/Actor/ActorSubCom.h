#pragma once
#include "InsEvent.h"
#include "Geometry.h"
#include "ZoneMisc.h"
#include "GCfg.h"

class Actor;
template<class SubComClass>
class ActorSubCom : public EventCom<SubComClass>
{
public:
	Actor &m_Actor;
public:
	ActorSubCom(EventMgr &owner, Actor &actor)
		:EventCom<SubComClass>(owner)
		, m_Actor(actor)
	{
	}
};

