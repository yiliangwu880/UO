#include "PacketsCom.h"

//c#适配
#define base Packet
#define uint uint32
#define byte uint8_t

UnicodeMessage::UnicodeMessage(uint32 serial, int graphic, MessageType type, int hue, int font, CStr &lang, CStr &name, CStr &text)
	: base(0xAE)
{
	static string slang = "ENU";
	CStr *pLang = &lang;
	if (lang.empty())
	{
		pLang = &slang;
	}

	if (hue == 0)
	{
		hue = 0x3B2;
	}

	EnsureCapacity(50 + (text.length() * 2));

	m_Stream.Write(serial);
	m_Stream.Write((short)graphic);
	m_Stream.Write((byte)type);
	m_Stream.Write((short)hue);
	m_Stream.Write((short)font);
	m_Stream.WriteAsciiFixed(*pLang, 4);
	m_Stream.WriteAsciiFixed(name, 30);
	m_Stream.WriteBigUniNull(text);
}
