#include "ActorMgr.h"
#include "Player/PlayerMgr.h"

Actor::Actor(ActorOwner &owner, EntityType t)
	:EventCom<Actor>(owner)
	, m_owner(owner)
	, m_ActorBase(*this, t)
	, m_ActorAttr(*this)
	, m_ActorEquip(*this)
	, m_Observer(*this, t)
	, m_StateMgr(*this)
	, m_BuffMgr(*this)
	, m_ActorBag(*this)
	, m_ActorSkill(*this)
{
	ActorMgr::Ins().AddActor(*this);
}

Actor::~Actor()
{
	ActorMgr::Ins().DelActor(m_ActorBase.GetId());
}

void Actor::InitMonster(const MonsterInit &data)
{
	//fire event init monster
	//m_ActorBase.InitMonster(data);
}

void Actor::EnterScene(uint32 id)
{
	Scene *p = SceneMgr::Ins().Find(id);
	L_COND_V(p);
	
	Point3D pos = m_ActorBase.GetPos();
	m_Observer.Enter(*p, pos.X, pos.Y);
}

bool Actor::EnterScene(Scene &scene, uint16 x, uint16 y)
{
	m_ActorBase.SetPos(Point3D(x, y, 0));
	return m_Observer.Enter(scene, x, y);
}

const std::string & Actor::Name() const
{
	return m_ActorBase.GetName();
}

::NetState * Actor::NetState()
{
	if (m_ActorBase.GetType() != EntityType::Player)
	{
		return nullptr;
	}
	Player *player = dynamic_cast<Player*>(&m_owner);
	L_COND(player, nullptr);
	return &(player->m_PlayerSn.m_ns);
}

void Actor::Send(Packet &packet)
{
	if (m_ActorBase.GetType() != EntityType::Player)
	{
		L_ERROR("");
		return;
	}
	Player *player = dynamic_cast<Player*>(&m_owner);
	L_COND_V(player);
	player->Send(packet);
}

void Actor::OnStatsQuery(Mobile &from)
{
	L_DEBUG("OnStatsQuery");
	//if (from.Map == Map && Utility.InUpdateRange(this, from) && from.CanSee(this))
	{
		MobileStatus rsp(from, *this);
		from.Send(rsp);
	}

	if (&from == this)
	{
		StatLockInfo rsp(*this);
		Send(rsp);
	}

	//IParty ip = m_Party as IParty;

	//if (ip != null)
	//{
	//	ip.OnStatsQuery(from, this);
	//}
}

void Actor::OnSkillsQuery(Mobile &from)
{
	if (&from == this)
	{
		L_DEBUG("OnSkillsQuery");
		SkillUpdate rsp(m_ActorSkill);
		Send(rsp);
	}
}

IWeapon *Actor::Weapon()
{
	SItem item;

	m_ActorEquip.GetItem(Layer::OneHanded);

	if (item == nullptr)
	{
		item = m_ActorEquip.GetItem(Layer::TwoHanded);
	}

	if (item == nullptr)
	{
		static Fists f;
		return &f;
	}
	return dynamic_cast<IWeapon*> (item.get());
}

int Actor::GetAOSStatus(int index)
{
	Actor &from = *this;
	switch (index)
	{
	case 0: return from.GetMaxResistance(ResistanceType::Physical);
	case 1: return from.GetMaxResistance(ResistanceType::Fire);
	case 2: return from.GetMaxResistance(ResistanceType::Cold);
	case 3: return from.GetMaxResistance(ResistanceType::Poison);
	case 4: return from.GetMaxResistance(ResistanceType::Energy);
	case 5: return 1;//std::min(45 + BaseArmor.GetRefinedDefenseChance(from), AosAttributes.GetValue(from, AosAttribute.DefendChance));
	case 6: return 1;//45 + BaseArmor.GetRefinedDefenseChance(from);
	case 7: return 1;//Math.Min(from.Race == Race.Gargoyle ? 50 : 45, AosAttributes.GetValue(from, AosAttribute.AttackChance));
	case 8: return 1;//Math.Min(60, AosAttributes.GetValue(from, AosAttribute.WeaponSpeed));
	case 9: return 1;//Math.Min(100, AosAttributes.GetValue(from, AosAttribute.WeaponDamage));
	case 10: return 1;//Math.Min(100, AosAttributes.GetValue(from, AosAttribute.LowerRegCost));
	case 11: return 1;//AosAttributes.GetValue(from, AosAttribute.SpellDamage);
	case 12: return 1;//Math.Min(6, AosAttributes.GetValue(from, AosAttribute.CastRecovery));
	case 13: return 1;//Math.Min(4, AosAttributes.GetValue(from, AosAttribute.CastSpeed));
	case 14: return 1;//Math.Min(40, AosAttributes.GetValue(from, AosAttribute.LowerManaCost)) + BaseArmor.GetInherentLowerManaCost(from);

	case 15: return 1;//RegenRates.HitPointRegen(from); // HP   REGEN
	case 16: return 1;//RegenRates.StamRegen(from); // Stam REGEN
	case 17: return 1;//RegenRates.ManaRegen(from); // MANA REGEN
	case 18: return 1;//Math.Min(105, AosAttributes.GetValue(from, AosAttribute.ReflectPhysical)); // reflect phys
	case 19: return 1;//Math.Min(50, AosAttributes.GetValue(from, AosAttribute.EnhancePotions)); // enhance pots

	case 20: return 1;//AosAttributes.GetValue(from, AosAttribute.BonusStr) + from.GetStatOffset(StatType.Str); // str inc
	case 21: return 1;//AosAttributes.GetValue(from, AosAttribute.BonusDex) + from.GetStatOffset(StatType.Dex); ; // dex inc
	case 22: return 1;//AosAttributes.GetValue(from, AosAttribute.BonusInt) + from.GetStatOffset(StatType.Int); ; // int inc

	case 23: return 0; // hits neg
	case 24: return 0; // stam neg
	case 25: return 0; // mana neg

	case 26: return 1;//AosAttributes.GetValue(from, AosAttribute.BonusHits); // hits inc
	case 27: return 1;//AosAttributes.GetValue(from, AosAttribute.BonusStam); // stam inc
	case 28: return 1;//AosAttributes.GetValue(from, AosAttribute.BonusMana); // mana inc
	default: 
		L_WARN("unknow idx =%d", index);
		return 0;
	}
}

int Actor::GetMaxResistance(ResistanceType type)
{
	return 100;
}

StatLockType Actor::StrLock()
{
	return StatLockType::Up;
}

StatLockType Actor::DexLock()
{
	return StatLockType::Up;
}

StatLockType Actor::IntLock()
{
	return StatLockType::Up;
}

Player * Actor::GetPlayer()
{
	if (m_ActorBase.GetType() != EntityType::Player)
	{
		return nullptr;
	}
	Player *player = dynamic_cast<Player*>(&m_owner);
	L_COND(player, nullptr);
	return player;
}

bool Actor::IsStaff()
{
	Player *p = GetPlayer();
	if (p == nullptr)
	{
		return false;
	}
	
	return (uint32)(p->m_PlayerMiscData.m_AccessLevel) >= (uint32)(AccessLevel::Counselor);
}

time_t & Actor::NextActionTime()
{
	return m_ActorMiscData.NextActionTime;
}

void Actor::SendActionMessage()
{
	if (m_ActorMiscData.m_NextActionMessage - Core::TickCount() >= 0)
	{
		return;
	}

	m_ActorMiscData.m_NextActionMessage = Core::TickCount() + 500;

	SendLocalizedMessage(500119); // You must wait to perform another action.

}

void Actor::OnPaperdollRequest()
{
	if (CanPaperdollBeOpenedBy(*this))
	{
		DisplayPaperdollTo(*this);
	}
}

void Actor::DisplayPaperdollTo(Actor &from)
{
	Mobile &beholder = from;
	Mobile &beheld = *this;

	DisplayPaperdoll msg(beheld, Titles::ComputeTitle(beholder, beheld), beheld.AllowEquipFrom(beholder));
	beholder.Send(msg);

	if (beholder.ViewOPL())
	{
		EquipSItems &items = beheld.m_ActorEquip.GetItems();

		for (uint32 i = 0; i < items.size(); ++i)
		{
			SItem &item = items[i];
			if (item == nullptr)
			{
				continue;
			}
			//beholder.Send(item.OPLPacket);
		}
		// NOTE: OSI sends MobileUpdate when opening your own paperdoll.
		// It has a very bad rubber-banding affect. What positive affects does it have?
	}
}

bool Actor::CanPaperdollBeOpenedBy(Actor &from)
{
	//return (Body.IsHuman || Body.IsGhost || IsBodyMod || from == this);
	return &from == this;
}

bool Actor::AllowEquipFrom(Mobile &from)
{
	return (&from == this || (from.AccessLevel() >= AccessLevel::Decorator && from.AccessLevel() > AccessLevel()));
}

::AccessLevel Actor::AccessLevel()
{
	Player *p = GetPlayer();
	if (nullptr == p)
	{
		L_ERROR("");
		return AccessLevel::Player;
	}
	return p->m_PlayerMiscData.m_AccessLevel;
}

void Actor::SendLocalizedMessage(int number)
{
	if (m_ActorBase.GetType() != EntityType::Player)
	{
		return;
	}
	Send(MessageLocalized::InstantiateGeneric(number));
}
