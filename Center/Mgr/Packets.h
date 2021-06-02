//发送消息包结构，参考 c#
#pragma once
#include "ComPackets.h"
#include "CenterMgr.h"
#include "ExpansionInfo.h"
#include "ComPackets.h"
//c#适配
#define base Packet
#define uint uint32
#define byte uint8_t



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

		if(1)//if (acct != null && acct.Limit >= 6)
		{
			flags |= (int)FeatureFlags::LiveAccount;
			flags &= ~(int)FeatureFlags::UOTD;

			if(1)//if (acct.Limit > 6)
			{
				flags |= (int)FeatureFlags::SeventhCharacterSlot;
			}
			else
			{
				flags |= (int)FeatureFlags::SixthCharacterSlot;
			}
		}

		if(1)//if (ns.ExtendedSupportedFeatures)
		{
			m_Stream.Write((uint)flags);
		}
		else
		{
			m_Stream.Write((ushort)flags);
		}
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
	CharacterList()
		: base(0xA9)
	{
		vector<CityInfo> info; //tmp
		{
			CityInfo city;
			city.Building = "New Haven Bank";
			city.City = "New Haven";
			city.Description = 1150168;
			city.m_Location = Point3D(3503, 2574, 14);
			city.X(3503);
			city.Y(2574);
			city.Z(14);
			info.push_back(city);
		}

		int a_Length = 7; // IAccount：：Length ？
		int a_Limit = 7;
		bool IsEnhancedClient = false;
		EnsureCapacity(11 + (a_Length * 60) + (info.size() * 89));

		int highSlot = -1;

		//for (int i = 0; i < a.Length; ++i)
		//{
		//	if (a[i] != null)
		//	{
		//		highSlot = i;
		//	}
		//}
		highSlot = -1; //没调试到上面注释赋值

		int count = max(max(highSlot + 1, a_Limit), 5);

		m_Stream.Write((byte)count);

		for (int i = 0; i < count; ++i)
		{
			//if (a[i] != null) //估计是已有角色
			//{
			//	m_Stream.WriteAsciiFixed(a[i].Name, 30);
			//	m_Stream.Fill(30); // password
			//}
			//else
			{
				m_Stream.Fill(60);
			}
		}

		m_Stream.Write((byte)info.size());

		for (int i = 0; i < (int)info.size(); ++i)
		{
			CityInfo ci = info[i];

			m_Stream.Write((byte)i);
			m_Stream.WriteAsciiFixed(ci.City, 32);
			m_Stream.WriteAsciiFixed(ci.Building, 32);
			m_Stream.Write(ci.X());
			m_Stream.Write(ci.Y());
			m_Stream.Write(ci.Z());
			m_Stream.Write(1);//(ci.Map.MapID);
			m_Stream.Write(ci.Description);
			m_Stream.Write(0);
		}

		int flags = (int)FeatureFlags::ExpansionEJ;//ExpansionInfo.CoreExpansion.CharacterListFlags;

		if (count > 6)
		{
			flags |= ((int)CharacterListFlags::SeventhCharacterSlot | (int)CharacterListFlags::SixthCharacterSlot);
		}
		// 7th Character Slot - TODO: Is SixthCharacterSlot Required?
		else if (count == 6)
		{
			flags |= (int)CharacterListFlags::SixthCharacterSlot; // 6th Character Slot
		}
		else if (a_Limit == 1)
		{
			flags |= ((int)CharacterListFlags::SlotLimit | (int)CharacterListFlags::OneCharacterSlot); // Limit Characters & One Character
		}

		if (IsEnhancedClient)
		{
			flags |= (int)CharacterListFlags::KR; // Suppport Enhanced Client / KR flag 1 and 2 (0x200 + 0x400)
		}

		//flags |= AdditionalFlags;

		//L_DEBUG("{0}: {1} / {2} [{3}]", a.Username, a.Count, a.Limit, flags);

		m_Stream.Write((int)flags);

		m_Stream.Write((short)-1);

		int disabled = 0;//ThirdPartyFeature disabled = FeatureProtection.DisabledFeatures;

		//if (disabled != 0)
		//{
		//	if (m_MD5Provider == null)
		//	{
		//		m_MD5Provider = new MD5CryptoServiceProvider();
		//	}

		//	m_Stream.UnderlyingStream.Flush();

		//	var hashCode = m_MD5Provider.ComputeHash(
		//		m_Stream.UnderlyingStream.GetBuffer(), 0, (int)m_Stream.UnderlyingStream.Length);
		//	var buffer = new byte[28];

		//	for (int i = 0; i < count; ++i)
		//	{
		//		Utility.RandomBytes(buffer);

		//		m_Stream.Seek(35 + (i * 60), SeekOrigin.Begin);
		//		m_Stream.Write(buffer, 0, buffer.Length);
		//	}

		//	m_Stream.Seek(35, SeekOrigin.Begin);
		//	m_Stream.Write((int)((long)disabled >> 32));
		//	m_Stream.Write((int)disabled);

		//	m_Stream.Seek(95, SeekOrigin.Begin);
		//	m_Stream.Write(hashCode, 0, hashCode.Length);
		//}
	}
	CharacterListFlags AdditionalFlags = CharacterListFlags::None;
};

//tmp Mobile
struct Mobile
{
	int Serial=92;
	int Body = 400;
	int X	=350;
	int Y	=257;
	int Z	=14	;
	Direction dir = Direction::North;

};

class LoginConfirm : public Packet
{
public:
	 LoginConfirm(Mobile m)
		: base(0x1B, 37)
	{
		m_Stream.Write(m.Serial);
		m_Stream.Write(0);
		m_Stream.Write((short)m.Body);
		m_Stream.Write((short)m.X);
		m_Stream.Write((short)m.Y);
		m_Stream.Write((short)m.Z);
		m_Stream.Write((byte)m.dir);
		m_Stream.Write((byte)0);
		m_Stream.Write(-1);

		//Map map = m.Map;

		//if (map == null || map == Map.Internal)
		//{
		//	map = m.LogoutMap;
		//}

		m_Stream.Write((short)0);
		m_Stream.Write((short)0);
		m_Stream.Write((short)(6144));//m_Stream.Write((short)(map == null ? 6144 : map.Width));
		m_Stream.Write((short)(4096));//m_Stream.Write((short)(map == null ? 4096 : map.Height));

		m_Stream.Fill();
	}
};

class MapChange : public Packet
{
public:
	 MapChange(Mobile m)
		: base(0xBF)
	{
		EnsureCapacity(6);

		m_Stream.Write((short)0x08);
		m_Stream.Write((byte)1);//((byte)(m.Map == null ? 0 : m.Map.MapID));
	}
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
