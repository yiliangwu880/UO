#pragma once
#include "StaticCfg/GCfg.h"
#include "dbStructDef.h"
#include "Aoi/Aoi.h"

class Item;
class Container;
class Scene;
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

using SItem = shared_ptr<Item>;
class Item
{

protected:
	Point3D m_pos;
	uint32 m_num = 1;
	const ItemCfg *m_cfg = nullptr;

	//below no save db
	/////////////////////
	uint32 m_id = 0;//memory id
	ItemObserver m_observer;
	weak_ptr<Container> m_parent;

public:
	virtual ~Item() {};
	virtual Layer GetLayer()const { return Layer::Invalid; }
	virtual void OnLoad(const DbItem &dbItemBase);
	virtual void OnSave(DbItem &dbItemBase);
	virtual void OnAdd(Container *parent);//this 被放置到parent. parant == nullptr 表示没有父容器
	virtual uint16 GetItemNum() const  { return 1; }//容器内物品数，包括嵌套的 和 容器自己

public:
	Item();
	uint32 Serial() const { return m_id; }
	uint16 GetHue() const { return m_cfg->hue; }
	void SetPos(uint16 x, uint16 y, uint16 z = 0);
	ItemType GetType() const;
	Container *GetParent();
	
};



//符石
//堆叠绑带



