#include "ItemMgr.h"
#include "dbStructPack.h"


Container::Container()
{

}

void Container::Add(SItem item)
{
	if (m_vecItem.size()>=m_maxItemNum)
	{
		L_ERROR("error call,  can't add item.container is full");//先判断能否加入
		return;
	}
	m_vecItem.push_back(item);
}

bool Container::EnableAdd(SItem item)
{
	if (m_vecItem.size() >= m_maxItemNum)
	{
		return false;
	}
	return true;
}

void Container::OnLoad(const DbItem &dbItem)
{
	Item::OnLoad(dbItem);

	DbContainer dbContainer;
	m_maxItemNum = dbContainer.maxItemNum;
	m_maxNestNum = dbContainer.maxNestNum;

	L_COND_V(db::UnpackStr(dbContainer, dbItem.data));
	for (const DbItem &item : dbContainer.vecItem)
	{
		shared_ptr<Item> p = ItemMgr::Ins().CreateItem(item);
		if (nullptr == p)
		{
			L_ERROR("create item  fail");
			continue;
		}
		p->OnLoad(item);
		m_vecItem.push_back(p);
	}
}

void Container::OnSave(DbItem &dbItem)
{
	Item::OnSave(dbItem);

	DbContainer dbContainer;
	dbContainer.maxItemNum = m_maxItemNum;
	dbContainer.maxNestNum = m_maxNestNum;
	for (shared_ptr<Item> &item : m_vecItem)
	{
		DbItem v;
		item->OnSave(v);
		dbContainer.vecItem.push_back(v);
	}
	L_COND_V(db::PackStr(dbContainer, dbItem.data));
}
