#pragma once
#include "InsEvent.h"
#include "Geometry.h"

class Actor;
class ActorBase : public EventCom<ActorBase>
{
	Actor &m_owner;
	DbActorBase m_base;
	Point3D m_pos; //内存用整个，存库再复制到m_base
public:
	ActorBase(Actor &owner);
	void Init(const DbActorBase &base);
	void OnSave(DbPlayer &data);
	const Point3D &GetPos() { return m_pos; };
};