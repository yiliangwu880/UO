#pragma once
#include "Item.h"


class ToolItem : public Item
{
	uint16 m_num=10; //剩余使用点

public:
	virtual void OnLoad(const DbItem &dbItem) override;
	virtual void OnSave(DbItem &dbItem) override;

public:
	ToolItem(uint16 cfgId);
};

