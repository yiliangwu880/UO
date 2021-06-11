//发送消息包结构，参考 c#
#pragma once
#include "ComPackets.h"
#include "ExpansionInfo.h"
#include "ComPackets.h"
//c#适配
#define base Packet
#define uint uint32
#define byte uint8_t


class Actor;
class LoginConfirm : public Packet
{
public:
	LoginConfirm(Actor &actor);
};

#undef base
#undef uint
#undef byte
