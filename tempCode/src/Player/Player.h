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

//�����
class TaskSys : public PlayerSubSys
{
	Player m_owner;
public:
	TaskSys(Player &owner)
		:PlayerSubSys(owner)
	{

		Reg<InsEventId::ChangeHp>(ChangeHp);//ע���¼�
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
	//PlayerSkill skill; �������ܣ�
	//friend dd;
	//money;
	Actor m_actor;//Actor�ڲ���������Ҫ��player���������֮��Ļ�����ֻ����event�ˡ�����ֱ�� ���������������ΪActor���ͨ��Monster,Npc������
	

public:
	Player()
		:m_actor(*this)
	{}
	void OnLoad(const PlayerDb &db)
	{
		m_actor.OnLoad(db);
		//������ϵͳ��otherSys.OnLoad(db);
	}
	void OnSave()
	{
		PlayerDb db;
		m_actor.Get(db);//��ȡ x,y,hp�ȵ� m_PlayerDb��
		//������ϵͳ��otherSys(m_PlayerDb);
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
	//��һ��ϵͳ�¼���ɾ��player
	void OnNextEvent()
	{
		m_id2Player.erase(id);
		m_waitDelPlayers.clear();
	}
};