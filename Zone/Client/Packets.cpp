#include "Packets.h"
#include "Player.h"
#include "svr_util/include/time/su_timestamp.h"
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
			L_DEBUG("send equip item， cfgid=0x%x", item->GetItemID());
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

void MobileStatus::WriteAttr(int current, int maximum)
{
	m_Stream.Write((short)current);
	m_Stream.Write((short)maximum);
}

void MobileStatus::WriteAttrNorm(int current, int maximum)
{
	AttributeNormalizer::WriteReverse(m_Stream, current, maximum);
}

MobileStatus::MobileStatus(Mobile &beholder, Mobile &beheld)
	: base(0x11)
{
	CStr &name = beheld.Name();
	const DbActorBase &d = beheld.m_ActorBase.GetData();
	const DbActorAttr &attr = beheld.m_ActorAttr.GetData();
	ActorBase &actorBase = beheld.m_ActorBase;
	ActorAttr &actorAttr = beheld.m_ActorAttr;

	int type;
	bool isEnhancedClient = false; //beholder.NetState != null && beholder.NetState.IsEnhancedClient;

	if (&beholder != &beheld)
	{
		type = 0;
		EnsureCapacity(43);
	}
	else
	{
		type = 6;
		EnsureCapacity(isEnhancedClient ? 151 : 121);
	}
	//else if (Core.ML && ns != null && ns.ExtendedStatus)
	//{
	//	type = 6;
	//	EnsureCapacity(isEnhancedClient ? 151 : 121);
	//}
	//else if (Core.ML && ns != null && ns.SupportsExpansion(Expansion.ML))
	//{
	//	type = 5;
	//	EnsureCapacity(91);
	//}
	//else
	//{
	//	type = Core.AOS ? 4 : 3;
	//	EnsureCapacity(88);
	//}

	m_Stream.Write(beheld.Serial());

	m_Stream.WriteAsciiFixed(name, 30);

	if (&beholder == &beheld)
	{
		WriteAttr(actorAttr.Hits(), actorAttr.HitsMax());
	}
	else
	{
		WriteAttrNorm(actorAttr.Hits(), actorAttr.HitsMax());
	}

	m_Stream.Write(false);//beheld.CanBeRenamedBy(beholder)

	m_Stream.Write((byte)type);

	if (type > 0)
	{
		m_Stream.Write(d.female);

		m_Stream.Write((short)attr.str);
		m_Stream.Write((short)attr.dex);
		m_Stream.Write((short)attr.intl);

		WriteAttr(beheld.m_ActorAttr.Stam(), beheld.m_ActorAttr.StamMax());
		WriteAttr(beheld.m_ActorAttr.Mana(), beheld.m_ActorAttr.ManaMax());

		m_Stream.Write(3000);//beheld.TotalGold
		m_Stream.Write((short)10);//Core.AOS ? beheld.PhysicalResistance : (int)(beheld.ArmorRating + 0.5)
		m_Stream.Write((short)30);//(Mobile.BodyWeight + beheld.TotalWeight)

		if (type >= 5)
		{
			m_Stream.Write((short)300);//beheld.MaxWeight
			m_Stream.Write((byte)(1)); //1 == human// beheld.Race.RaceID + 1 Would be 0x00 if it's a non-ML enabled account but...
		}

		m_Stream.Write((short)225); //beheld.StatCap

		m_Stream.Write((byte)0);		 //beheld.Followers);
		m_Stream.Write((byte)5);	 //beheld.FollowersMax)

		if (type >= 4)
		{
			m_Stream.Write((short)1);//beheld.FireResistance); // Fire
			m_Stream.Write((short)1);//beheld.ColdResistance); // Cold
			m_Stream.Write((short)1);//beheld.PoisonResistance); // Poison
			m_Stream.Write((short)1);//beheld.EnergyResistance); // Energy
			m_Stream.Write((short)1);//beheld.Luck); // Luck

		//	IWeapon weapon = beheld.Weapon;

			int min = 0, max = 0;

			//if (weapon != null)
			//{
			//	weapon.GetStatusDamage(beheld, out min, out max);
			//}

			m_Stream.Write((short)1); // Damage min
			m_Stream.Write((short)7); // Damage max

			m_Stream.Write(0);//beheld.TithingPoints
		}

		if (type >= 6)
		{
			int count = isEnhancedClient ? 28 : 14;

			for (int i = 0; i <= count; ++i)
			{
				m_Stream.Write((short)0);//beheld.GetAOSStatus(i)
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
