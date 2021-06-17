//发送消息包结构，参考 c#
#pragma once
#include "PacketsBase.h"
#include "ExpansionInfo.h"
//c#适配
#define base Packet
#define uint uint32
#define byte uint8_t


struct UnicodeMessage : Packet
{
	UnicodeMessage(uint32 serial, int graphic, MessageType type, int hue, int font, CStr &lang, CStr &name, CStr &text);
};

#undef base
#undef uint
#undef byte
