//zone svr 可复用 
#pragma once
#include "InsEvent.h"
#include "Geometry.h"

class MonsterCfg;
class Scene;
class Actor;
class Item;
struct MonsterInit
{
	const MonsterCfg *cfg = nullptr;
	Scene *scene = nullptr;
	Point2D pos;
};

class IEntity
{
public:
	virtual uint32 Serial() = 0;
};

class ActorOwner : public EventMgr, public Noncopyable
{
public:
	DbActor &m_DbActor;

public:
	ActorOwner(DbActor &dbActor);
	virtual ~ActorOwner();
};


using SItem = shared_ptr<Item>;
class World
{
public:
	static Actor *FindMobile(uint32 id);
	static SItem FindItem(uint32 id);
};

class Titles
{
public:
	static string ComputeTitle(Actor &beholder, Actor &beheld);
};