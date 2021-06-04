#include "CPackets.h"
#include "Account/AccountMgr.h"

//c#适配
#define base Packet
#define uint uint32
#define byte uint8_t

CharacterList::CharacterList(Account &acc)
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

	int a_Length = MAX_CHAR_NUM_IN_ACC; // IAccount：：Length ？
	int a_Limit = MAX_CHAR_NUM_IN_ACC;
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

	const std::vector<db::ActorBrief> &vecActor = acc.m_AccData.GetActorList();
	for (int i = 0; i < count; ++i)
	{
		if (i < (int)vecActor.size())
		{
			m_Stream.WriteAsciiFixed(vecActor[i].name.c_str(), MAX_CHAR_NAME);
			m_Stream.Fill(MAX_CHAR_NAME); // password
		}
		else
		{
			m_Stream.Fill(MAX_CHAR_NAME);
			m_Stream.Fill(MAX_CHAR_NAME);
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