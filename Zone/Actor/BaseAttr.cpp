#include "Actor.h"

BaseAttr::BaseAttr(Actor &owner)
	:EventCom<BaseAttr>(owner.m_owner)
	,m_owner(owner)
{

}
