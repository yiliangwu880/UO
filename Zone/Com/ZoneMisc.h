//zone svr 可复用 
#pragma once
#include "InsEvent.h"
#include "Geometry.h"

class MonsterCfg;
class Scene;
class Actor;
struct MonsterInit
{
	const MonsterCfg *cfg = nullptr;
	Scene *scene = nullptr;
	Point2D pos;
};


class ActorOwner : public EventMgr, public Noncopyable
{
public:
	virtual ~ActorOwner();
};


class World
{
public:
	static Actor *FindMobile(uint32 id);
};

class Titles
{
public:
	static string ComputeTitle(Actor &beholder, Actor &beheld);
};