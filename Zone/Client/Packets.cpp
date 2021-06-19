#include "Packets.h"
#include "Player.h"
#include "svr_util/include/time/su_timestamp.h"
#include <cstdarg>
#include <stdio.h>
#include <stdlib.h>
#include "ZoneMisc.h"

//c#适配
#define base Packet
#define uint uint32
#define byte uint8_t
using Mobile = Actor;

LoginConfirm::LoginConfirm(Actor &actor)
	: base(0x1B, 37)
{
	ActorBase &m = actor.m_ActorBase;
	const DbActorBase &d = m.GetData();
	m_Stream.Write(m.GetId());
	m_Stream.Write(0);
	m_Stream.Write((short)d.body);
	m_Stream.Write((short)d.x);
	m_Stream.Write((short)d.y);
	m_Stream.Write((short)d.z);
	m_Stream.Write((byte)d.dir);
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

MapChange::MapChange(Actor &actor)
	: base(0xBF)
{
	EnsureCapacity(6);

	m_Stream.Write((short)0x08);
	m_Stream.Write((byte)(actor.m_ActorBase.GetMapId()));
}


MobileIncoming::MobileIncoming(Actor &beholder, Actor &beheld)
	: base(0x78)
{
	const DbActorBase &dbActoBase = beheld.m_ActorBase.GetData();
	//可能是为了一次发送中，避免重复发送相同layer item内容
	int m_Version = 0;
	std::array<int, 256> m_DupedLayers = {};

	++m_Version;

	auto eq = beheld.m_ActorEquip.GetItems();
	int count = eq.size();

	if (dbActoBase.hairItemID > 0)
	{
		count++;
	}

	if (dbActoBase.facialHairItemID > 0)
	{
		count++;
	}

	if (dbActoBase.faceItemID > 0)
	{
		count++;
	}

	EnsureCapacity(23 + (count * 9));
	int hue = dbActoBase.hue;

	//if (beheld.SolidHueOverride >= 0)
	//{
	//	hue = beheld.SolidHueOverride;
	//}

	m_Stream.Write(beheld.m_ActorBase.GetId());
	m_Stream.Write((short)dbActoBase.body);
	m_Stream.Write((short)dbActoBase.x);
	m_Stream.Write((short)dbActoBase.y);
	m_Stream.Write((sbyte)dbActoBase.z);
	m_Stream.Write((byte)dbActoBase.dir);
	m_Stream.Write((short)hue);
	m_Stream.Write((byte)0x10);//m_Stream.Write((byte)beheld.GetPacketFlags());
	m_Stream.Write((byte)Notoriety::Innocent);

	for (size_t i = 0; i < eq.size(); ++i)
	{
		SItem item = eq[i];
		if (item == nullptr)
		{
			continue;
		}
		byte layer = (byte)item->GetLayer();

		if (beholder.CanSee(item) && m_DupedLayers[layer] != m_Version)
		{
			m_DupedLayers[layer] = m_Version;
			L_DEBUG("send equip item， cfgid=0x%x layer=0x%x", item->GetItemID(), layer);
			hue = item->GetHue();

			//if (beheld.SolidHueOverride >= 0)
			//{
			//	hue = beheld.SolidHueOverride;
			//}

			int itemID = item->GetItemID() & 0xFFFF;

			m_Stream.Write(item->Serial());
			m_Stream.Write((ushort)itemID);
			m_Stream.Write(layer);

			m_Stream.Write((short)hue);
		}
	}

	if (dbActoBase.hairItemID > 0)
	{
		if (m_DupedLayers[(int)Layer::Hair] != m_Version)
		{
			m_DupedLayers[(int)Layer::Hair] = m_Version;
			hue = dbActoBase.hairHue;



			int itemID = dbActoBase.hairItemID & 0xFFFF;

			m_Stream.Write(HairInfo::FakeSerial(beheld));
			m_Stream.Write((ushort)itemID);
			m_Stream.Write((byte)Layer::Hair);

			m_Stream.Write((short)hue);
		}
	}

	if (dbActoBase.facialHairItemID > 0)
	{
		if (m_DupedLayers[(int)Layer::FacialHair] != m_Version)
		{
			m_DupedLayers[(int)Layer::FacialHair] = m_Version;
			hue = dbActoBase.facialHairHue;



			int itemID = dbActoBase.facialHairItemID & 0xFFFF;

			m_Stream.Write(FacialHairInfo::FakeSerial(beheld));
			m_Stream.Write((ushort)itemID);
			m_Stream.Write((byte)Layer::FacialHair);

			m_Stream.Write((short)hue);
		}
	}

	if (dbActoBase.faceItemID > 0)
	{
		if (m_DupedLayers[(int)Layer::Face] != m_Version)
		{
			m_DupedLayers[(int)Layer::Face] = m_Version;
			hue = dbActoBase.faceHue;

			int itemID = dbActoBase.faceItemID & 0xFFFF;

			m_Stream.Write(FaceInfo::FakeSerial(beheld));
			m_Stream.Write((ushort)itemID);
			m_Stream.Write((byte)Layer::Face);

			m_Stream.Write((short)hue);
		}
	}

	m_Stream.Write(0); // terminate
}

MobileUpdate::MobileUpdate(Mobile &m)
	: base(0x20, 19)
{
	const auto &data = m.m_ActorBase.GetData();
	int32 hue = data.hue;

	//if (m.SolidHueOverride >= 0)
	//{
	//	hue = m.SolidHueOverride;
	//}

	m_Stream.Write(m.Serial());
	m_Stream.Write((short)data.body);
	m_Stream.Write((byte)0);
	m_Stream.Write((short)hue);
	m_Stream.Write((byte)0x10);//m_Stream.Write((byte)m.GetPacketFlags());
	m_Stream.Write((short)data.x);
	m_Stream.Write((short)data.y);
	m_Stream.Write((short)0);
	m_Stream.Write((byte)data.dir);
	m_Stream.Write((sbyte)data.z);
}

PersonalLightLevel::PersonalLightLevel(Mobile &m, int level)
	: base(0x4E, 6)
{
	m_Stream.Write(m.Serial());
	m_Stream.Write((byte)level);
}

SetWarMode::SetWarMode(bool mode)
	: base(0x72, 5)
{
	m_Stream.Write(mode);
	m_Stream.Write((byte)0x00);
	m_Stream.Write((byte)0x32);
	m_Stream.Write((byte)0x00);
}

LogPacket::LogPacket(bool isFixed)
	: base(0x1B, isFixed ? 1 : 0)
{
	m_isFixed = isFixed;
}
//@str 内容为 "1B 0“，，包写入内容2字节，字符串的16进制值 
void LogPacket::SetHexLog(CStr &src)
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


void MobileStatus::WriteAttr(int current, int maximum)
{
	m_Stream.Write((short)current);
	m_Stream.Write((short)maximum);
}

void MobileStatus::WriteAttrNorm(int current, int maximum)
{
	AttributeNormalizer::WriteReverse(m_Stream, current, maximum);
}
//
//MobileStatus::MobileStatus(Mobile &beholder, Mobile &beheld)
//	: base(0x11)
//{
//	CStr &name = beheld.Name();
//	const DbActorBase &d = beheld.m_ActorBase.GetData();
//	const DbActorAttr &attr = beheld.m_ActorAttr.GetData();
//	ActorBase &actorBase = beheld.m_ActorBase;
//	ActorAttr &actorAttr = beheld.m_ActorAttr;
//
//	int type;
//	bool isEnhancedClient = false; //beholder.NetState != null && beholder.NetState.IsEnhancedClient;
//
//	if (&beholder != &beheld)
//	{
//		type = 0;
//		EnsureCapacity(43);
//	}
//	else
//	{
//		type = 6;
//		EnsureCapacity(isEnhancedClient ? 151 : 121);
//	}
//	//else if (Core.ML && ns != null && ns.ExtendedStatus)
//	//{
//	//	type = 6;
//	//	EnsureCapacity(isEnhancedClient ? 151 : 121);
//	//}
//	//else if (Core.ML && ns != null && ns.SupportsExpansion(Expansion.ML))
//	//{
//	//	type = 5;
//	//	EnsureCapacity(91);
//	//}
//	//else
//	//{
//	//	type = Core.AOS ? 4 : 3;
//	//	EnsureCapacity(88);
//	//}
//
//	m_Stream.Write(beheld.Serial());
//
//	m_Stream.WriteAsciiFixed(name, 30);
//
//	if (&beholder == &beheld)
//	{
//		WriteAttr(actorAttr.Hits(), actorAttr.HitsMax());
//	}
//	else
//	{
//		WriteAttrNorm(actorAttr.Hits(), actorAttr.HitsMax());
//	}
//
//	m_Stream.Write(false);//beheld.CanBeRenamedBy(beholder)
//
//	m_Stream.Write((byte)type);
//
//	if (type > 0)
//	{
//		m_Stream.Write(d.female);
//
//		m_Stream.Write((short)attr.str);
//		m_Stream.Write((short)attr.dex);
//		m_Stream.Write((short)attr.intl);
//
//		WriteAttr(beheld.m_ActorAttr.Stam(), beheld.m_ActorAttr.StamMax());
//		WriteAttr(beheld.m_ActorAttr.Mana(), beheld.m_ActorAttr.ManaMax());
//
//		m_Stream.Write(3000);//beheld.TotalGold
//		m_Stream.Write((short)10);//Core.AOS ? beheld.PhysicalResistance : (int)(beheld.ArmorRating + 0.5)
//		m_Stream.Write((short)30);//(Mobile.BodyWeight + beheld.TotalWeight)
//
//		if (type >= 5)
//		{
//			m_Stream.Write((short)300);//beheld.MaxWeight
//			m_Stream.Write((byte)(1)); //1 == human// beheld.Race.RaceID + 1 Would be 0x00 if it's a non-ML enabled account but...
//		}
//
//		m_Stream.Write((short)225); //beheld.StatCap
//
//		m_Stream.Write((byte)0);		 //beheld.Followers);
//		m_Stream.Write((byte)5);	 //beheld.FollowersMax)
//
//		if (type >= 4)
//		{
//			m_Stream.Write((short)1);//beheld.FireResistance); // Fire
//			m_Stream.Write((short)1);//beheld.ColdResistance); // Cold
//			m_Stream.Write((short)1);//beheld.PoisonResistance); // Poison
//			m_Stream.Write((short)1);//beheld.EnergyResistance); // Energy
//			m_Stream.Write((short)1);//beheld.Luck); // Luck
//
//		//	IWeapon weapon = beheld.Weapon;
//
//			int min = 0, max = 0;
//
//			//if (weapon != null)
//			//{
//			//	weapon.GetStatusDamage(beheld, out min, out max);
//			//}
//
//			m_Stream.Write((short)1); // Damage min
//			m_Stream.Write((short)7); // Damage max
//
//			m_Stream.Write(0);//beheld.TithingPoints
//		}
//
//		if (type >= 6)
//		{
//			int count = isEnhancedClient ? 28 : 14;
//
//			for (int i = 0; i <= count; ++i)
//			{
//				m_Stream.Write((short)0);//beheld.GetAOSStatus(i)
//			}
//		}
//	}
//}
//

MobileStatus::MobileStatus(Mobile &beholder, Mobile &beheld)
	: base(0x11)
{
	NetState *ns = beheld.NetState();
	CStr &name = beheld.Name();

	int type;
	bool isEnhancedClient = false;

	if (&beholder != &beheld)
	{
		type = 0;
		EnsureCapacity(43);
	}
	else if (Core::ML && ns != nullptr)
	{
		type = 6;
		EnsureCapacity(isEnhancedClient ? 151 : 121);
	}
	else
	{
		type = Core::AOS ? 4 : 3;
		EnsureCapacity(88);
	}

	m_Stream.Write(beheld.Serial());

	m_Stream.WriteAsciiFixed(name, 30);

	if (&beholder == &beheld)
	{
		WriteAttr(beheld.Hits(), beheld.HitsMax());
	}
	else
	{
		WriteAttrNorm(beheld.Hits(), beheld.HitsMax());
	}

	m_Stream.Write(beheld.CanBeRenamedBy(beholder));

	m_Stream.Write((byte)type);

	if (type > 0)
	{
		m_Stream.Write(beheld.Female());

		m_Stream.Write((short)beheld.Str());
		m_Stream.Write((short)beheld.Dex());
		m_Stream.Write((short)beheld.Int());

		WriteAttr(beheld.Stam(), beheld.StamMax());
		WriteAttr(beheld.Mana(), beheld.ManaMax());

		m_Stream.Write(beheld.TotalGold());
		m_Stream.Write((short)(beheld.PhysicalResistance()));
		m_Stream.Write((short)(Mobile::BodyWeight + beheld.TotalWeight()));

		if (type >= 5)
		{
			m_Stream.Write((short)beheld.MaxWeight());
			m_Stream.Write((byte)(beheld.RaceID() + 1)); // Would be 0x00 if it's a non-ML enabled account but...
		}

		m_Stream.Write((short)beheld.StatCap());

		m_Stream.Write((byte)beheld.Followers());
		m_Stream.Write((byte)beheld.FollowersMax());

		if (type >= 4)
		{
			m_Stream.Write((short)beheld.FireResistance()); // Fire
			m_Stream.Write((short)beheld.ColdResistance()); // Cold
			m_Stream.Write((short)beheld.PoisonResistance()); // Poison
			m_Stream.Write((short)beheld.EnergyResistance()); // Energy
			m_Stream.Write((short)beheld.Luck()); // Luck

			IWeapon *weapon = beheld.Weapon();

			int min = 0, max = 0;

			if (weapon != nullptr)
			{
				weapon->GetStatusDamage(beheld,  min, max);
			}

			m_Stream.Write((short)min); // Damage min
			m_Stream.Write((short)max); // Damage max

			m_Stream.Write(beheld.TithingPoints());
		}

		if (type >= 6)
		{
			int count = isEnhancedClient ? 28 : 14;

			for (int i = 0; i <= count; ++i)
			{
				m_Stream.Write((short)beheld.GetAOSStatus(i));
			}
		}
	}
}


void AttributeNormalizer::Write(PacketWriter stream, uint32 cur, uint32 max)
{
	if (m_Enabled && max != 0)
	{
		stream.Write((short)m_Maximum);
		stream.Write((short)((cur * m_Maximum) / max));
	}
	else
	{
		stream.Write((short)max);
		stream.Write((short)cur);
	}
}

void AttributeNormalizer::WriteReverse(PacketWriter stream, uint32 cur, uint32 max)
{
	if (m_Enabled && max != 0)
	{
		stream.Write((short)((cur * m_Maximum) / max));
		stream.Write((short)m_Maximum);
	}
	else
	{
		stream.Write((short)cur);
		stream.Write((short)max);
	}
}

SeasonChange::SeasonChange(int season /*= 0*/, bool playSound /*= true*/)
	: base(0xBC, 3)
{
	m_Stream.Write((byte)season);
	m_Stream.Write(playSound);
}

CurrentTime::CurrentTime()
	: base(0x5B, 4)
{
	const tm &d = SysTime::Ins().CurTm();
	m_Stream.Write((byte)d.tm_hour);
	m_Stream.Write((byte)d.tm_min);
	m_Stream.Write((byte)d.tm_sec);
}

PingAck::PingAck(byte ping)
	: base(0x73, 2)
{
	m_Stream.Write(ping);
}

GlobalLightLevel::GlobalLightLevel(int level)
	: base(0x4F, 2)
{
	m_Stream.Write((byte)level);
}

MovementAck::MovementAck(int seq, Notoriety noto)
	: base(0x22, 3)
{
	m_Stream.Write((byte)seq);
	m_Stream.Write((byte)noto);
}

StatLockInfo::StatLockInfo(Mobile &m)
	: base(0xBF)
{
	EnsureCapacity(12);

	m_Stream.Write((short)0x19);

	if (false)//(m.NetState().IsEnhancedClient)
	{
		m_Stream.Write((byte)5);
	}
	else
	{
		m_Stream.Write((byte)2);
	}

	m_Stream.Write(m.Serial());
	m_Stream.Write((byte)0);

	int lockBits = 0;

	lockBits |= (int)m.StrLock() << 4;
	lockBits |= (int)m.DexLock() << 2;
	lockBits |= (int)m.IntLock();

	m_Stream.Write((byte)lockBits);
}

SkillUpdate::SkillUpdate(ActorSkill &skills)
	: base(0x3A)
{
	EnsureCapacity(6 + (skills.Length() * 9));

	m_Stream.Write((byte)0x02); // type: absolute, capped

	for (uint32 i = 0; i < skills.Length(); ++i)
	{
		Skill *p = skills.GetSkill(i);
		if (p == nullptr)
		{
			L_ERROR("");
			return;
		}
		Skill &s = *p;
		double v = 100; //s.NonRacialValue;
		int uv = (int)(v * 10);

		if (uv < 0)
		{
			uv = 0;
		}
		else if (uv >= 0x10000)
		{
			uv = 0xFFFF;
		}
		const SkillCfg *cfg = s.GetCfg();
		if (cfg == nullptr)
		{
			L_ERROR("");
			return;
		}
		m_Stream.Write((ushort)(cfg->skillID + 1));
		m_Stream.Write((ushort)uv);
		m_Stream.Write((ushort)s.BaseFixedPoint());
		m_Stream.Write((byte)s.Lock());
		m_Stream.Write((ushort)s.CapFixedPoint());
	}

	m_Stream.Write((short)0); // terminate
}

std::unordered_map<int, std::shared_ptr<MessageLocalized>> MessageLocalized::cache;

MessageLocalized & MessageLocalized::InstantiateGeneric(int number)
{
	MessageLocalized *point = nullptr;
	auto it = cache.find(number);
	if (it == cache.end())
	{
		auto s = make_shared<MessageLocalized>(Serial::MinusOne, -1, MessageType::Regular, 0x3B2, 3, number, "System", "");
		s->SetStatic();
		point = s.get();
		cache.insert(make_pair(number, s));
	}
	else
	{
		shared_ptr< MessageLocalized> s = it->second;
		point = s.get();
	}

	MessageLocalized &p = *point;
	return p;
}

MessageLocalized::MessageLocalized(uint32 serial, int graphic, MessageType type, int hue, int font, int number, string name, string args)
	: base(0xC1)
{
	if (hue == 0)
	{
		hue = 0x3B2;
	}

	EnsureCapacity(50 + (args.length() * 2));// 要不要*2？待研究

	m_Stream.Write(serial);
	m_Stream.Write((short)graphic);
	m_Stream.Write((byte)type);
	m_Stream.Write((short)hue);
	m_Stream.Write((short)font);
	m_Stream.Write(number);
	m_Stream.WriteAsciiFixed(name, 30);
	m_Stream.WriteLittleUniNull(args);
}

DisplayPaperdoll::DisplayPaperdoll(Mobile &m, string text, bool canLift)
	: base(0x88, 66)
{
	byte flags = 0x00;

	if (m.Warmode())
	{
		flags |= 0x01;
	}

	if (canLift)
	{
		flags |= 0x02;
	}

	m_Stream.Write(m.Serial());
	m_Stream.WriteAsciiFixed(text, 60);
	m_Stream.Write(flags);
}

OPLInfo::OPLInfo(ObjectPropertyList &list)
	: base(0xDC, 9)
{
	m_Stream.Write(list.Entity().Serial());
	m_Stream.Write(list.Hash());
}

ObjectPropertyList::ObjectPropertyList(IEntity &e)
	: base(0xD6)
	, m_Entity(e)
{
	EnsureCapacity(128);

	m_Stream.Write((short)1);
	m_Stream.Write(e.Serial());
	m_Stream.Write((byte)0);
	m_Stream.Write((byte)0);
	m_Stream.Write(e.Serial());
}

void ObjectPropertyList::Add(int number, const char* fmt, ...)
{
	string resultOUT;
	va_list vl;
	va_start(vl, fmt);

	resultOUT.resize(1024, 0);
	int len;
	for (;;)
	{
		len = vsnprintf((char *)resultOUT.c_str(), resultOUT.size(), fmt, vl);
		if (len == -1)
		{
			resultOUT.clear();
			break;
		}
		if (len >= (int)resultOUT.size())
		{
			resultOUT.resize(resultOUT.size() * 2, 0);
			va_start(vl, fmt);
			continue;
		}
		break;
	}
	resultOUT.resize(len);

	va_end(vl);

	Add(number, resultOUT);
}

void ObjectPropertyList::Add(const char* fmt, ...)
{
	string resultOUT;
	va_list vl;
	va_start(vl, fmt);

	resultOUT.resize(1024, 0);
	int len;
	for (;;)
	{
		len = vsnprintf((char *)resultOUT.c_str(), resultOUT.size(), fmt, vl);
		if (len == -1)
		{
			resultOUT.clear();
			break;
		}
		if (len >= (int)resultOUT.size())
		{
			resultOUT.resize(resultOUT.size() * 2, 0);
			va_start(vl, fmt);
			continue;
		}
		break;
	}
	resultOUT.resize(len);

	va_end(vl);
	Add(GetStringNumber(), resultOUT);
}

void ObjectPropertyList::Add(int number, CStr &arguments)
{
	if (number == 0)
	{
		return;
	}

	if (m_Header == 0)
	{
		m_Header = number;
		m_HeaderArgs = arguments;
	}

	AddHash(number);
	AddHash(std::hash<std::string>()(arguments));

	m_Stream.Write(number);

	string out;
	Encoding::Ins().Unicode(arguments, out); 

	m_Stream.Write((short)out.length());
	m_Stream.Write(out.c_str(), 0, out.length());
}

void ObjectPropertyList::Add(int number)
{
	if (number == 0)
	{
		return;
	}

	AddHash(number);

	if (m_Header == 0)
	{
		m_Header = number;
		m_HeaderArgs = "";
	}

	m_Stream.Write(number);
	m_Stream.Write((short)0);
}


void ObjectPropertyList::Terminate()
{
	m_Stream.Write(0);

	m_Stream.Seek(11, SeekOrigin::Begin);//指针设置到偏移11位置
	m_Stream.WriteBySeek(m_Hash); //覆盖写入索引 
}

void ObjectPropertyList::AddHash(int val)
{
	m_Hash ^= (val & 0x3FFFFFF);
	m_Hash ^= (val >> 26) & 0x3F;
}
