#pragma once
#include "Npc.h"


class NpcMgr : public Singleton<NpcMgr>
{
	unordered_map<uint32, Npc *> m_all;
public:
	Npc *Create();
	Npc *Find(uint32 uin);
	void Del(uint32 uin);
public:


private:
};
