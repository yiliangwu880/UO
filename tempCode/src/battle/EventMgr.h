#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>

enum ActorEventId
{
	ChangeHp,
	InterUp,//打断技能

};

//定义事件ID 关联 接收函数参数列表
template<int ID>
struct EventTraits {
	using Fun = int;
};

template<>
struct EventTraits< ChangeHp>{
	using Fun std::function<void(int &update)>;
	template<class T, class C>
	Fun Bind(T cb, C *m_owner)
	{
		return std::bind(cb, m_owner, _1);
	}
};

//继承后，能让对象注册成员函数为事件函数
class EventReg
{
	EventMgr m_owner;
public:
	//用户注意：this 是owner的组合对象（成员变量）
	//通常一个类就构造函数写，减少出错的机会.和 比直接写注册传递指针 大大减少出错机会
	EventReg(EventMgr &owner);

	//Reg 注册this 成员函数到  this owner 事件管理器。能保证事件回调不野
	template<int ID, class T>
	void Reg(T cb)
	{
		m_owner.Reg<ID>(cb, this);
	}

	template<int ID, class T>
	void UnReg(T cb)
	{
		m_owner.UnReg<ID>(cb);
	}
	virtual void Init(cfg);
};

class EventMgr
{
	template<class Fun>
	struct SubscribeSet
	{
		std::set<void*> m_funs;//void* 表示任意类型回调函数
		bool m_is_firing = false; //true表示触发回调中
		std::set<void*> m_cacheRegFuns;
		std::set<void*> m_cacheUnRegFuns;
	};
	std::unordered_map<ActorEventId, SubscribeSet > m_idfuns;

	std::unordered_map<void *, void *> m_fun2funObj; //成员函数地址 2 函数对象地址
	bool m_isForbiding=false;
public:
	~EventMgr()
	{
		m_isForbiding = true;
	}
	template<int ID, class ... Args>
	void FireEvent(Args&& ... args)
	{
		if (Forbiding())
		{
			return;
		}
		auto &ss = inner::GetChannel<ID>();

		ss.m_is_firing = true;
		for (const auto &v : ss.m_funs)
		{
			v(std::forward<Args>(args)...);//这里不好通用地调用类成员函数指针（理论上可以，但是需要研究复杂的实现），所以用函数对象实现比较保险。
		}
		ss.m_is_firing = false;
		if (!ss.m_cacheRegFuns.empty())
		{
			ss.m_funs.insert(ss.m_cacheRegFuns.begin(), ss.m_cacheRegFuns.end());
		}
		if (!ss.m_cacheRegFuns.empty())
		{
			ss.m_funs.insert(ss.m_cacheRegFuns.begin(), ss.m_cacheRegFuns.end());
		}
	}
private:
	//cb 为类成员函数。注意：需要用户保证事件回调时， ins不野。
	//函数私有，不让用户直接危险地使用。
	template<int ID, class T, class C>
	void Reg(T cb, C *ins)
	{
		if (m_fun2funObj[cb])
		{
			//repeated reg
			return;
		}
		auto ff = EventTraits<ID>::Bind(cb, ins);
		void *funObj = mgr.RegEvent<ID>(ff);
		m_fun2funObj[cb] = p;
	}

	template<int ID, class T>
	void UnReg(T cb)
	{
		mgr.UnRegEvent<ID>(m_fun2funObj[cb]);
	}
	//具体注册， fun是强类型检查
	template<const int ID>
	void * RegEvent(typename EventTraits<ID>::Fun fun)
	{
		using FunObj = typename EventTraits<ID>::Fun;
		FunObj *p = new FunObj(fun)
			auto &ss = m_idfuns[ID];
		if (ss.m_is_firing) //触发回调过程，延后插入触发
		{
			ss.m_cacheRegFuns.insert(p);
			return;
		}
		ss.m_funs.insert(p);
		return p;
	}
	template<const int ID>
	void UnRegEvent(void *p)
	{
		auto &ss = m_idfuns[ID];
		if (ss.m_is_firing) //触发回调过程，延后插入触发
		{
			ss.m_cacheUnRegFuns.erase(p);
			return;
		}
		ss.m_funs.erase(p);
	}
};



template<class T>
class EventReg
{
	EventMgr mgr;
public:

	void Reg<ChangeHp>(T cb, C *m_owner)
	{
		auto ff = EventTraits<ChangeHp>::Bind(cb, m_owner);
		mgr.RegEvent<ChangeHp>(ff);
	}
private:
	void EventCb();
};

