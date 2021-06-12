#pragma once
#include "StaticCfg/GCfg.h"

class ItemBase
{
	uint32 m_id = 0;//memory id
	const ItemCfg *m_cfg = nullptr;
	Point3D m_pos;

public:
	ItemBase(uint16 cfgId);
	virtual ~ItemBase() {};
	uint32 Serial() const { return m_id; }
	uint16 GetHue() const { return m_cfg->hue; }
	virtual Layer GetLayer()const { return Layer::Invalid; }
};

class Weapon : public ItemBase
{
	//attr
};

class Dress : public ItemBase
{

};
class TailorStone : public ItemBase
{

};

class Container
{
	//vector items
};


