#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>


template<class T>
class BaseWeak
{
	std::shared_ptr<T> sp;
public:
	BaseWeak()
		:sp((T*)this, [](T*) {})
	{}

	std::weak_ptr<T> WeakPtr() { return sp; };
};


class Scene
{
public:
private:
};

class ActorSubSys
{
	Actor m_owner;
public:
	ActorSubSys(Actor &owner);
	template<int ID>
	void Reg<ID>(T cb)
	{
		m_owner.Reg<ID>(cb, this);
	}

	template<int ID>
	void UnReg<ID>(T cb)
	{
		mgr.UnReg<ID>(cb);
	}
};




