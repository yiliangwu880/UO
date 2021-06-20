#include "ItemMgr.h"
#include "SceneMgr.h"
#include "ZoneMisc.h"
#include "Packets.h"
#include "ActorMgr.h"

ItemObserver::ItemObserver(Item &item)
	:Aoi::Entity(EntityType::Item)
	, m_Item(item)
{

}
void ItemObserver::OnAddObserver(Entity &other)
{

}

void ItemObserver::OnDelObserver(Entity &other)
{

}


bool ItemObserver::Enter(Scene &scene, uint16_t x, uint16_t y)
{
	bool r = Aoi::Entity::Enter(scene.m_aoi, x, y);
	if (r)
	{
		m_Item.SetPos(x, y);
	}

	m_Item.OnAdd();
	return r;
}

bool ItemObserver::Leave()
{
	return Aoi::Entity::Leave();
}


Item::Item(uint16 cfgId)
	:m_observer(*this)
{
	m_id = Serial::NewItem();
	m_ItemID = cfgId;
	const ItemCfg *p = gCfg.GetItemCfg(cfgId);
	if (nullptr == p)
	{
		L_ERROR("find item cfg error. id=%d", cfgId);
		p = gCfg.GetItemCfg(0xE21);
		m_ItemID = 0xE21;
	}
	m_cfg = p;
}

ObjectPropertyList & Item::PropertyList()
{
	if (m_PropertyList == nullptr)
	{
		m_PropertyList =  make_unique<ObjectPropertyList>(*this);
		GetProperties(*(m_PropertyList.get()));
		//AppendChildProperties(m_PropertyList); //npc售价相关

		m_PropertyList->Terminate();
		m_PropertyList->SetStatic();
	}

	return *(m_PropertyList.get());
}

void Item::GetProperties(ObjectPropertyList &list)
{
	AddNameProperties(list);

	//if (Spawner != null)
	//{
	//	Spawner.GetSpawnProperties(this, list);
	//}
}


void Item::AddNameProperties(ObjectPropertyList &list)
{
	AddNameProperty(list);

	if (IsSecure())
	{
		//AddSecureProperty(list);
		list.Add(501644); // locked down & secure
	}
	else if (IsLockedDown())
	{
		//AddLockedDownProperty(list);
		list.Add(501643); // locked down
	}

	if (HonestyItem())
	{
		AddHonestyProperty(list);
	}

#if 0
	Mobile blessedFor = BlessedFor;

	if (blessedFor != null && !blessedFor.Deleted)
	{
		//AddBlessedForProperty(list, blessedFor);
		list.Add(1062203, "%d", "aa"); // Blessed for ~1_NAME~
	}
#endif

	if (DisplayLootType())
	{
		AddLootTypeProperty(list);
	}

	if (DisplayWeight())
	{
		AddWeightProperty(list);
	}

	if (QuestItem())
	{
		//AddQuestItemProperty(list);
		list.Add(1072351); // Quest Item
	}

	AppendChildNameProperties(list);
}

void Item::AppendChildNameProperties(ObjectPropertyList &list)
{
	//npc售卖 相关
	//if (m_Parent is Item)
	//{
	//	((Item)m_Parent).GetChildNameProperties(list, this);
	//}
	//else if (m_Parent is Mobile)
	//{
	//	((Mobile)m_Parent).GetChildNameProperties(list, this);
	//}
}

void Item::AddWeightProperty(ObjectPropertyList &list)
{
	if (m_cfg->weight == 0)
		return;

	int weight = PileWeight(); //+ TotalWeight();

	if (weight == 1)
	{
		list.Add(1072788, StrNum::NumToStr(weight)); //Weight: ~1_WEIGHT~ stone
	}
	else
	{
		list.Add(1072789, StrNum::NumToStr(weight)); //Weight: ~1_WEIGHT~ stones
	}
}

int Item::PileWeight()
{ 
	return m_cfg->weight * m_Amount; 
}

void Item::AddLootTypeProperty(ObjectPropertyList &list)
{
	if (m_LootType == LootType::Blessed)
	{
		list.Add(1038021); // blessed
	}
	else if (m_LootType == LootType::Cursed)
	{
		list.Add(1049643); // cursed
	}
	else if (Insured())
	{
		list.Add(1061682); // <b>insured</b>
	}
}

void Item::AddHonestyProperty(ObjectPropertyList &list)
{
	//if (m_HonestyPickup != DateTime.MinValue)
	//{
	//	int minutes = (int)(m_HonestyPickup + TimeSpan.FromHours(3) - DateTime.UtcNow).TotalMinutes;
	//	list.Add(1151914, minutes.ToString()); // Minutes remaining for credit: ~1_val~
	//}

	//list.Add(1151520); // lost item (Return to gain Honesty)

	list.Add(1151914, "30");
}

void Item::AddNameProperty(ObjectPropertyList &list)
{
	CStr &name = Name();

	if (name.empty())
	{
		if (m_Amount <= 1)
		{
			list.Add(LabelNumber());
		}
		else
		{
			list.Add(1050039, "%d\t#%d", m_Amount, LabelNumber()); // ~1_NUMBER~ ~2_ITEMNAME~
		}
	}
	else
	{
		if (m_Amount <= 1)
		{
			list.Add(name);
		}
		else
		{
			list.Add(1050039, "%d\t%d", m_Amount, Name()); // ~1_NUMBER~ ~2_ITEMNAME~
		}
	}
}
int Item::LabelNumber()
{
	if (m_ItemID < 0x4000)
	{
		return 1020000 + m_ItemID;
	}
	else
	{
		return 1078872 + m_ItemID;
	}
}

Item::~Item()
{

}

void Item::OnLoad(const DbItem &dbItem)
{
	m_pos = Point3D(dbItem.dbItemBase.x, dbItem.dbItemBase.y, 0);
	m_Amount = dbItem.dbItemBase.num;
}

void Item::OnSave(DbItem &dbItem)
{
	dbItem.dbItemBase.cfgId = m_ItemID;
	dbItem.dbItemBase.num = m_Amount;
	dbItem.dbItemBase.x = m_pos.X;
	dbItem.dbItemBase.y = m_pos.Y;
}

Container * Item::GetParentContainer()const
{
	if (shared_ptr<IEntity> p = m_parent.lock())
	{
		return dynamic_cast<Container *>(p.get());
	}
	return nullptr;
}

void Item::OnAdd(weak_ptr<IEntity> parent)
{
	if (Container *pc = GetParentContainer())
	{
		pc->Remove(this);
	}

	m_parent.reset();
	m_parent = parent;
}

void Item::SetPos(uint16 x, uint16 y, uint16 z /*= 0*/)
{
	m_pos = Point3D(x, y, z);
}

ItemType Item::GetType() const
{
	return m_cfg->type;
}

Packet & Item::OPLPacket()
{
	if (m_OPLInfo == nullptr)
	{
		m_OPLInfo = make_unique<OPLInfo>(PropertyList());
	}
	return *(m_OPLInfo.get());
}

su::CStr & Item::Name()
{
	return m_cfg->name;
}

Actor * Item::GetParentActor()const
{
	shared_ptr<IEntity> p = m_parent.lock();
	if (p == nullptr)
	{
		return nullptr;
	}
	else if(Container *c = dynamic_cast<Container *>(p.get()))
	{
		return c->GetParentActor();
	}
	else if (Actor *actor = dynamic_cast<Actor *>(p.get()))
	{
		return actor;
	}
	else
	{
		L_ERROR("unknow");
		return nullptr;
	}
}




