#pragma once
#include "Item.h"


class ToolItem : public Item
{
	friend class ItemMgr;


	uint16 m_num=10; //剩余使用点

public:
	virtual void OnLoad(const DbItem &dbItem) override;
	virtual void OnSave(DbItem &dbItem) override;

private:
	ToolItem(uint16 cfgId);
};

