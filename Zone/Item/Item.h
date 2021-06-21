#pragma once
#include "StaticCfg/GCfg.h"
#include "dbStructDef.h"
#include "Aoi/Aoi.h"
#include "ZoneMisc.h"
#include "ContextMenu.h"

class Item;
class Container;
class Scene;
class ItemMgr;
class OPLInfo;
class ObjectPropertyList;


using SItem = shared_ptr<Item>;

class ItemObserver : public Aoi::Entity
{
	Item &m_Item;

private:
	virtual void OnAddObserver(Entity &other); //other 看见我
	virtual void OnDelObserver(Entity &other); //other 看不见我

public:
	ItemObserver(Item &item);
	bool Enter(Scene &scene, uint16_t x, uint16_t y);
	bool Leave();
};


class Item : public IEntity
{
	friend class ItemMgr;

protected:
	Point3D m_pos;
	uint32 m_Amount = 1;
	const ItemCfg *m_cfg = nullptr;
	uint16 m_ItemID = 0; //ItemCfg id

	//below no save db
	/////////////////////
	uint32 m_id = 0;//memory id
	uint32 m_hue = 0;
	ItemObserver m_observer;
	LootType m_LootType = LootType::Blessed;
	//物品存放父节点。 m_parent.expired() 表示world上, 有值表示是 Container 或者 Actor
	weak_ptr<IEntity> m_parent; 

	unique_ptr<OPLInfo> m_OPLInfo;
	unique_ptr<ObjectPropertyList> m_PropertyList;

public:
	virtual ~Item();
	virtual Layer GetLayer()const { return Layer::Invalid; }
	virtual void OnLoad(const DbItem &dbItemBase);
	virtual void OnSave(DbItem &dbItemBase);
	virtual void OnAdd(weak_ptr<IEntity> parent= weak_ptr<IEntity>());//this 被放置到parent. parant == nullptr 表示没有父容器
	virtual uint16 GetItemNum() const  { return 1; }//容器内物品数，包括嵌套的 和 容器自己
	virtual uint32 Serial() { return m_id; };
	virtual CStr &Name();
	virtual void GetContextMenuEntries(Actor &from, vector<SContextMenuEntry> &list);
	

public:
	uint32 GetHue() const { return m_hue; }
	void SetPos(uint16 x, uint16 y, uint16 z = 0);
	ItemType GetType() const;
	Container * GetParentContainer() const;
	uint16 GetItemID() const { return m_ItemID; }
	Packet &OPLPacket();
	Actor *GetParentActor() const;

protected:
	Item(uint16 cfgId); //不让用户直接构造

private:
	ObjectPropertyList &PropertyList();
	void GetProperties(ObjectPropertyList &list);
	void AddNameProperties(ObjectPropertyList &list);
	void AddNameProperty(ObjectPropertyList &list);
	int LabelNumber();
	bool IsSecure() { return false; }
	bool IsLockedDown() { return false; }
	bool HonestyItem() { return false; }
	bool QuestItem() { return false; }
	bool DisplayLootType() { return true; }
	bool DisplayWeight() { return true; }
	bool Insured() { return true; }
	int PileWeight();
	void AddHonestyProperty(ObjectPropertyList &list);
	void AddLootTypeProperty(ObjectPropertyList &list);
	void AddWeightProperty(ObjectPropertyList &list);
	void AppendChildNameProperties(ObjectPropertyList &list);
};



//符石
//堆叠绑带



