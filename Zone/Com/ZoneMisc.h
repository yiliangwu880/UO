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

//管理 item mobile等对象 的内存标识
class Serial : public Singleton<Serial>
{
	uint32 m_LastMobile = 0;
	uint32 m_LastItem = 0x40000000;

public:
	uint32 NewMobile()
	{
		//                int 可以存放, 假设秒一个物品
		//4,294,967,295 sec
		//= 49,710 天
		// = 136年
		m_LastMobile++;
		return m_LastMobile;
	}

	uint32 NewItem()
	{
		m_LastItem++;
		return m_LastItem;
	}
	bool IsMobile(uint32 m_Serial){ return (m_Serial > 0 && m_Serial < 0x40000000); }
	bool IsItem(uint32 m_Serial) { return (m_Serial >= 0x40000000 && m_Serial <= 0x7FFFFFFF); }
};