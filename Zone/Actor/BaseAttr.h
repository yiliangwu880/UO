#pragma once
#include "InsEvent.h"

class Actor;
class BaseAttr : public EventCom<BaseAttr>
{
	Actor &m_owner;
public:
	BaseAttr(Actor &owner);

};