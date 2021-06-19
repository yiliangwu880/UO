//发送消息包结构，参考 c#
#pragma once
#include "PacketsBase.h"
#include "CenterMgr.h"
#include "ExpansionInfo.h"
#include "PacketsBase.h"
//c#适配
#define base Packet
#define uint uint32
#define byte uint8_t


class Account;

class AccountLoginAck : public Packet
{
public:
	 AccountLoginAck(const vector<ServerInfo> &info)
		: Packet(0xA8)
	{
		EnsureCapacity(6 + (info.size() * 40));

		m_Stream.Write((byte)0x5D); // Unknown

		m_Stream.Write((ushort)info.size());

		for (int i = 0; i < (int)info.size(); ++i)
		{
			ServerInfo si = info[i];

			m_Stream.Write((ushort)i);
			m_Stream.WriteAsciiFixed(si.Name, 32);
			m_Stream.Write((byte)si.FullPercent);
			m_Stream.Write((sbyte)si.TimeZone);
			m_Stream.Write(si.Address.Address);//(Utility.GetAddressValue(si.Address.Address));
		}
	}
};

class PlayServerAck : public Packet
{
public:
	 PlayServerAck(const ServerInfo &si, uint auth)
		: base(0x8C, 11)
	{
		//int addr = Utility.GetAddressValue(si.Address.Address);
		 int addr = si.Address.Address;
		 m_Stream.Write((byte)addr);
		 m_Stream.Write((byte)(addr >> 8));
		 m_Stream.Write((byte)(addr >> 16));
		 m_Stream.Write((byte)(addr >> 24));

		 m_Stream.Write((short)si.Address.Port);
		 m_Stream.Write(auth);
	}
};


class SupportedFeatures : public Packet
{
public:
	SupportedFeatures()
		: base(0xB9, 5)// base(0xB9, ns.ExtendedSupportedFeatures ? 5 : 3)
	{
		int flags = (int)FeatureFlags::ExpansionEJ;//ExpansionInfo.CoreExpansion.SupportedFeatures;


		//IAccount acct = ns.Account;

		//if(gTrue)//if (acct != null && acct.Limit >= 6)
		{
			flags |= (int)FeatureFlags::LiveAccount;
			flags &= ~(int)FeatureFlags::UOTD;

			//if(gTrue)//if (acct.Limit > 6)
			{
				flags |= (int)FeatureFlags::SeventhCharacterSlot;
			}
			//else
			//{
			//	flags |= (int)FeatureFlags::SixthCharacterSlot;
			//}
		}

		//if(gTrue)//if (ns.ExtendedSupportedFeatures)
		{
			m_Stream.Write((uint)flags);
		}
		//else
		//{
		//	m_Stream.Write((ushort)flags);
		//}
		{//temp B9 0 FF 92 DB
			char ar[5]={ (char)0xB9, (char)0x0 , (char)0xFF , (char)0x92 , (char)0xDB };
			string t;
			t.append(ar, 5);
			m_Stream.DebugReset(t);
		}
	}
};

//读取C#日志内容包
class LogPacket : public Packet
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

class CharacterList : public Packet
{
public:
	CharacterList(Account &acc);
	CharacterListFlags AdditionalFlags = CharacterListFlags::None;
};

class MapPatches : public Packet
{
public:
	 MapPatches()
		: base(0xBF)
	{
		EnsureCapacity(9 + (3 * 8));

		m_Stream.Write((short)0x0018);

		m_Stream.Write(4);

		//m_Stream.Write(Map.Felucca.Tiles.Patch.StaticBlocks);
		//m_Stream.Write(Map.Felucca.Tiles.Patch.LandBlocks);

		//m_Stream.Write(Map.Trammel.Tiles.Patch.StaticBlocks);
		//m_Stream.Write(Map.Trammel.Tiles.Patch.LandBlocks);

		//m_Stream.Write(Map.Ilshenar.Tiles.Patch.StaticBlocks);
		//m_Stream.Write(Map.Ilshenar.Tiles.Patch.LandBlocks);

		//m_Stream.Write(Map.Malas.Tiles.Patch.StaticBlocks);
		//m_Stream.Write(Map.Malas.Tiles.Patch.LandBlocks);


		m_Stream.Write((int)0);
		m_Stream.Write((int)0);
		m_Stream.Write((int)0);
		m_Stream.Write((int)0);
		m_Stream.Write((int)0);
		m_Stream.Write((int)0);
		m_Stream.Write((int)0);
		m_Stream.Write((int)0);

		//TODO: Should this include newer facets?
	}
};


#undef base
#undef uint
#undef byte
