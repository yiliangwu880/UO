#pragma once
#include "Item.h"


class Container : public Item
{
	uint8 m_maxItemNum = 10; //最大物品数
	uint8 m_maxNestNum = 3; //最大嵌套容器数
	vector<SItem> m_vecItem;

public:
	virtual void OnLoad(const DbItem &dbItem) override;
	virtual void OnSave(DbItem &dbItem) override;

public:
	Container();
	void Add(SItem item);
	bool EnableAdd(SItem item);
};


