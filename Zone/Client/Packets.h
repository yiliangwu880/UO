//发送消息包结构，参考 c#
#pragma once
#include "PacketsBase.h"
#include "ExpansionInfo.h"
#include "PacketsBase.h"
//c#适配
#define base Packet
#define uint uint32
#define byte uint8_t


class Actor;
using Mobile = Actor;
class ActorSkill;
class IEntity;
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

struct ObjectPropertyList : Packet
{
	IEntity &m_Entity;
	int m_Hash;
	int m_Header;
	int m_Strings;
	string m_HeaderArgs;

	IEntity &Entity() { return m_Entity; } 
	int Hash() { return 0x40000000 + m_Hash;  }

	int Header(){ return m_Header; }//get set, set还没做，用的时候加
	string HeaderArgs(){ return m_HeaderArgs; }//

	static const bool Enabled = true; //=Core.AOS;

	ObjectPropertyList(IEntity &e);

	void Add(int number);

	void Terminate();

	//private static byte[] m_Buffer = new byte[1024];
	//private static readonly Encoding m_Encoding = Encoding.Unicode;

	void AddHash(int val);

	void Add(int number, CStr &arguments);

	void Add(int number, const char* fmt, ...);

	// Each of these are localized to "~1_NOTHING~" which allows the string argument to be used
	constexpr static const int m_StringNumbers[2]={1042971, 1070722};
	int GetStringNumber(){return m_StringNumbers[m_Strings++ % 2];}

	void Add(CStr &text){Add(GetStringNumber(), text);}

	void Add(const char* fmt, ...);

};


struct OPLInfo : Packet
{
	OPLInfo(ObjectPropertyList &list);
};

struct MessageLocalized : Packet
{
	static unordered_map<int, shared_ptr<MessageLocalized>> cache;

	static MessageLocalized &InstantiateGeneric(int number);

	MessageLocalized(
		uint32 serial, int graphic, MessageType type, int hue, int font, int number, string name, string args);
};

struct DisplayPaperdoll : Packet
{
	DisplayPaperdoll(Mobile &m, string text, bool canLift);
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
struct MovementAck : Packet
{
	MovementAck(int seq, Notoriety noto);
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
	LogPacket(bool isFixed);
	//@str 内容为 "1B 0“，，包写入内容2字节，字符串的16进制值 
	void SetHexLog(CStr &src);
};

struct StatLockInfo : Packet
{
	StatLockInfo(Mobile &m);
};

struct SkillUpdate : Packet
{
	SkillUpdate(ActorSkill &skills);
};

#undef base
#undef uint
#undef byte
