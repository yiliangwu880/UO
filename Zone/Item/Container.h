#pragma once
#include "Item.h"

class Container : public Item, public WeakPtr<Container>
{
	friend class ItemMgr;

	uint8 m_maxItemNum = 10; //最大物品数
	uint8 m_maxNestNum = 3;  //最大嵌套容器数. this 可以存放容器，嵌套多少个
	vector<SItem> m_vecItem;

	//below no save db
	//////////////////////////////////////////////////////////////////////////
	uint16 m_itemNum = 1;		//容器内物品数，包括嵌套的 和 容器自己

public:
	virtual void OnLoad(const DbItem &dbItem) override;
	virtual void OnSave(DbItem &dbItem) override;
	virtual uint16 GetItemNum() const override { return m_itemNum; }
	virtual Layer GetLayer()const override { return Layer::Backpack; }

public:
	void Add(SItem item);//里面会自动调用 Remove，把item从旧容器移除
	bool EnableAdd(SItem item) const;
	void Remove(Item *item);


private:
	Container(uint16 cfgId);
	uint32 GetNestNum() const;	//this 嵌套数，世界场景上 或者 actor上，为0，嵌套一层加1
	uint32 GetSubNestNum() const; //this 存放容器，最大嵌套数。 如果没有存放任何容器。返回0
	uint32 GetRootMaxNestNum()const; //root容器最大嵌套数
};


