#pragma once
#include "Monster.h"

class MonsterMgr : public Singleton<MonsterMgr>
{
	unordered_map<uint32, shared_ptr<Monster>> m_all;

public:
	static void OnFinishWorld();

public:
	Monster *Create();
	Monster *Find(uint32 uin);
	void Del(uint32 uin);
public:


private:
};
