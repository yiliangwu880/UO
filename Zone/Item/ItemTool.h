#pragma once
#include "Item.h"


class ItemTool : public Item
{
	friend class ItemMgr;


	uint16 m_Amount=10; //剩余使用点

public:
	virtual void OnLoad(const DbItem &dbItem) override;
	virtual void OnSave(DbItem &dbItem) override;

private:
	ItemTool(uint16 cfgId);
};

