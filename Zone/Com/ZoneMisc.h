//zone svr 可复用 
#pragma once
#include "InsEvent.h"
#include "Geometry.h"

class MonsterCfg;
class Scene;
struct MonsterInit
{
	const MonsterCfg *cfg = nullptr;
	Scene *scene = nullptr;
	Point2D pos;
};


class ActorOwner : public EventMgr, public Noncopyable
{
public:
};