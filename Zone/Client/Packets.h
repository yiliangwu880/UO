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
using Mobile = Actor;
class LoginConfirm : public Packet
{
public:
	LoginConfirm(Actor &actor);
};
struct MapChange : Packet
{
	MapChange(Actor &actor);
};

struct MobileIncoming : Packet
{
	//@beholder 客户端接收消息 actor, 
	//@beheld 打包成消息内容的 actor
	MobileIncoming(Actor &beholder, Actor &beheld);
};

struct PingAck : Packet
{
	PingAck(byte ping);
};

struct GlobalLightLevel : Packet
{
	GlobalLightLevel(int level);
};

struct PersonalLightLevel : Packet
{
	PersonalLightLevel(Mobile &m, int level);
};

struct MobileUpdate : Packet
{
	MobileUpdate(Mobile &m);

};

struct LoginComplete : Packet
{
	LoginComplete()
		: base(0x55, 1)
	{ }
};
//war or peace
struct SetWarMode : Packet
{
	SetWarMode(bool mode);
};


class AttributeNormalizer
{
	static const uint32 m_Maximum = 25;
	static const bool m_Enabled = true;

public:
	static void Write(PacketWriter stream, uint32 cur, uint32 max);

	static void WriteReverse(PacketWriter stream, uint32 cur, uint32 max);

};

struct SeasonChange : Packet
{
	SeasonChange(int season = 0, bool playSound = true);
};
struct CurrentTime : Packet
{
	CurrentTime();
};

struct MobileStatus : Packet
{
	MobileStatus(Mobile &beholder, Mobile &beheld);

	void WriteAttr(int current, int maximum);

	void WriteAttrNorm(int current, int maximum);
};

//读取C#日志内容包
struct LogPacket : public Packet
{
	bool m_isFixed = false;
public:
	//isFixed == true 固定长度包，所有内容等用户设定
	//isFixed == false 可变长度包，所有内容等用户设定
	LogPacket(bool isFixed)
		: base(0x1B, isFixed ? 1 : 0)
	{
		m_isFixed = isFixed;
	}
	//@str 内容为 "1B 0“，，包写入内容2字节，字符串的16进制值 
	void SetHexLog(CStr &src)
	{
		m_Stream.m_Stream.clear();
		VecStr out;
		StrUtil::split(src, " ", out);
		for (CStr &s : out)
		{
			uint8_t b = (uint8_t)std::stoi(s.c_str(), nullptr, 16);
			m_Stream.m_Stream.WriteByte(b);
		}
		if (m_isFixed)
		{
			m_Length = (int)out.size();
		}
	}
};
#undef base
#undef uint
#undef byte
