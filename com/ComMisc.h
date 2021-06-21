/*
	杂项
*/

#pragma once

template<class Owner>
class SubCom
{
public:
	Owner &m_owner;
public:
	SubCom(Owner &owner)
		:m_owner(owner)
	{

	}
};

struct Core
{
	static const bool T2A = true;
	static const bool UOR = true;
	static const bool UOTD = true;
	static const bool LBR = true;
	static const bool AOS = true;
	static const bool SE = true;
	static const bool ML = true;
	static const bool SA = true;
	static const bool HS = true;
	static const bool TOL = true;
	static const bool EJ = true;

	static const uint32 GlobalUpdateRange = 18;

	//ms millisecond
	static long TickCount();
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
	static Serial Zero;

public:
	static uint32 NewMobile();
	static uint32 NewItem();
	static bool IsMobile(uint32 m_Serial) { return (m_Serial > 0 && m_Serial < 0x40000000); }
	static bool IsItem(uint32 m_Serial) { return (m_Serial >= 0x40000000 && m_Serial <= 0x7FFFFFFF); }
};