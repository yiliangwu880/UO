/*
*/
#pragma once

#include <vector>
#include <map>
#include <functional>
#include "com.h"
#include "cfg.h"


class PlayerSubSys : public EventReg
{
	Player m_owner;
public:
	BaseState(Player &owner)
		:EventReg(owner)
	{}

};

//活动积分
class TaskSys : public PlayerSubSys
{
	Player m_owner;
public:
	TaskSys(Player &owner)
		:PlayerSubSys(owner)
	{

		Reg<InsEventId::ChangeHp>(ChangeHp);//注册事件
	}

	void ChangeHp(int &update)
	{
	}
	//
};



struct PlayerDb
{
	int dbid;
	int x, y;
	int hp;
};
class Player : public EventMgr;
{
public:
	//PlayerSkill skill; 升级技能；
	//friend dd;
	//money;
	Actor m_actor;//Actor内部出发，需要和player的其他组件之间的互动，只能用event了。不能直接 引用其他组件。因为Actor设计通用Monster,Npc等生物
	

public:
	Player()
		:m_actor(*this)
	{}
	void OnLoad(const PlayerDb &db)
	{
		m_actor.OnLoad(db);
		//其他子系统，otherSys.OnLoad(db);
	}
	void OnSave()
	{
		PlayerDb db;
		m_actor.Get(db);//获取 x,y,hp等到 m_PlayerDb；
		//其他子系统，otherSys(m_PlayerDb);
		sendtoDb(db);
	}
private:
};

class PlayerMgr
{
	std::map<int, Player> m_id2Player;
	std::set<int> m_waitDelPlayers;
	su::Timer tm;
public:
	void Remove(int  id)
	{
		m_waitDelPlayers.insert(id);
		if (tm.State() ==S_WAIT_START_TIMER )
		{
			tm.StartTimer(0, std::bind(&OnNextEvent, this));
		}
	}
	//下一个系统事件，删除player
	void OnNextEvent()
	{
		m_id2Player.erase(id);
		m_waitDelPlayers.clear();
	}
};