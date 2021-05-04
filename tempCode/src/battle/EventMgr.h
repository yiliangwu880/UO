#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>

enum ActorEventId
{
	ChangeHp,
	InterUp,//��ϼ���

};

//�����¼�ID ���� ���պ��������б�
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

//�̳к����ö���ע���Ա����Ϊ�¼�����
class EventReg
{
	EventMgr m_owner;
public:
	//�û�ע�⣺this ��owner����϶��󣨳�Ա������
	//ͨ��һ����͹��캯��д�����ٳ���Ļ���.�� ��ֱ��дע�ᴫ��ָ�� �����ٳ������
	EventReg(EventMgr &owner);

	//Reg ע��this ��Ա������  this owner �¼����������ܱ�֤�¼��ص���Ұ
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
		std::set<void*> m_funs;//void* ��ʾ�������ͻص�����
		bool m_is_firing = false; //true��ʾ�����ص���
		std::set<void*> m_cacheRegFuns;
		std::set<void*> m_cacheUnRegFuns;
	};
	std::unordered_map<ActorEventId, SubscribeSet > m_idfuns;

	std::unordered_map<void *, void *> m_fun2funObj; //��Ա������ַ 2 ���������ַ
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
			v(std::forward<Args>(args)...);//���ﲻ��ͨ�õص������Ա����ָ�루�����Ͽ��ԣ�������Ҫ�о����ӵ�ʵ�֣��������ú�������ʵ�ֱȽϱ��ա�
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
	//cb Ϊ���Ա������ע�⣺��Ҫ�û���֤�¼��ص�ʱ�� ins��Ұ��
	//����˽�У������û�ֱ��Σ�յ�ʹ�á�
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
	//����ע�ᣬ fun��ǿ���ͼ��
	template<const int ID>
	void * RegEvent(typename EventTraits<ID>::Fun fun)
	{
		using FunObj = typename EventTraits<ID>::Fun;
		FunObj *p = new FunObj(fun)
			auto &ss = m_idfuns[ID];
		if (ss.m_is_firing) //�����ص����̣��Ӻ���봥��
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
		if (ss.m_is_firing) //�����ص����̣��Ӻ���봥��
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

