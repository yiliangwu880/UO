#pragma once
#include "StaticCfg/GCfg.h"
#include "dbStructDef.h"
#include "Aoi/Aoi.h"

class Item;
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
	uint32 m_id = 0;//memory id
	Point3D m_pos;
	uint32 num = 1;
	const ItemCfg *m_cfg = nullptr;
	ItemObserver m_observer;

public:
	virtual ~Item() {};
	virtual Layer GetLayer()const { return Layer::Invalid; }
	virtual void OnLoad(const DbItem &dbItemBase);
	virtual void OnSave(DbItem &dbItemBase);

public:
	Item();
	uint32 Serial() const { return m_id; }
	uint16 GetHue() const { return m_cfg->hue; }
	void SetPos(uint16 x, uint16 y, uint16 z = 0);
	
};



//符石
//堆叠绑带



