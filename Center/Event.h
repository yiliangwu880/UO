#pragma once

#include "game_util/publish_subscribe.h"
//100��ʼ
enum Event
{
	EV_CFG_INI = 1,
	EV_START = 2, 
	EV_ON_EXIT = 3, //���̽���
};

namespace su
{
	//template<>
	//struct EventTraits<Event::CFG_INI> {
	//	using Fun = void(*)(); //Ĭ���¼��������ͣ����Բ��ö��� EventTraits
	//};

}
