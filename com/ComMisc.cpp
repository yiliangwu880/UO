
#include "ComMisc.h"
#include "svr_util/include/time/su_timestamp.h"

long Core::TickCount()
{
	return su::SysTime::Ins().Ms();
}


Serial::Serial(uint32 id)
	:m_id(id)
{
}

uint32 Serial::m_LastMobile = 0;

uint32 Serial::m_LastItem = 0x40000000;

Serial Serial::MinusOne(-1);

Serial Serial::Zero(0);

uint32 Serial::NewMobile()
{
	//                int 可以存放, 假设秒一个物品
	//4,294,967,295 sec
	//= 49,710 天
	// = 136年
	m_LastMobile++;
	return m_LastMobile;
}

uint32 Serial::NewItem()
{
	m_LastItem++;
	return m_LastItem;
}