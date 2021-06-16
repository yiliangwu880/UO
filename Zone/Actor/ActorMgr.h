
#pragma once
#include "Actor.h"

//弱引用所有actor
//注意： 必须要求actor的拥有者销毁方式是 post 才能保证一般调用函数使用不野
class ActorMgr : public Singleton<ActorMgr>
{
	unordered_map<uint32, WActor> m_id2Actor;

public:
	void AddActor(Actor &actor);
	void DelActor(uint32 id);
	Actor *Find(uint32 id);

};