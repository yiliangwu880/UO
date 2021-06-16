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

//管理 item mobile等对象 的内存标识
class Serial : public Singleton<Serial>
{
	uint32 m_id;

public:
	Serial(uint32 id);
	bool IsMobile() { return IsMobile(m_id); }
	bool IsItem() { return IsItem(m_id); }
	operator uint32() { return m_id; }

public:
	static uint32 m_LastMobile;
	static uint32 m_LastItem;
	static Serial MinusOne;
	static Serial Zero ;

public:
	static uint32 NewMobile();
	static uint32 NewItem();
	static bool IsMobile(uint32 m_Serial){ return (m_Serial > 0 && m_Serial < 0x40000000); }
	static bool IsItem(uint32 m_Serial) { return (m_Serial >= 0x40000000 && m_Serial <= 0x7FFFFFFF); }

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