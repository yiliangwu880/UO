#include "ItemMgr.h"
#include "dbStructPack.h"


void Container::OnLoad(const DbItem &dbItem)
{
	Item::OnLoad(dbItem);

	DbContainer dbContainer;
	L_COND_V(db::UnpackStr(dbContainer, dbItem.data));
	m_maxItemNum = dbContainer.maxItemNum;
	m_maxNestNum = dbContainer.maxNestNum;

	for (const DbItem &dbItem : dbContainer.vecItem)
	{
		SItem item = ItemMgr::Ins().CreateItem(dbItem);
		if (nullptr == item)
		{
			L_ERROR("create item  fail");
			continue;
		}
		item->OnLoad(dbItem);

		item->OnAdd(this);
		m_vecItem.push_back(item);
		m_itemNum += item->GetItemNum();
	}
}

void Container::OnSave(DbItem &dbItem)
{
	Item::OnSave(dbItem);

	DbContainer dbContainer;
	dbContainer.maxItemNum = m_maxItemNum;
	dbContainer.maxNestNum = m_maxNestNum;
	for (SItem &item : m_vecItem)
	{
		DbItem v;
		item->OnSave(v);
		dbContainer.vecItem.push_back(v);
	}
	L_COND_V(db::PackStr(dbContainer, dbItem.data));
}

void Container::Add(SItem item)
{
	L_COND_V(EnableAdd(item));
	item->OnAdd(this);
	m_vecItem.push_back(item);
	m_itemNum += item->GetItemNum();
}

bool Container::EnableAdd(SItem item) const
{
	if (m_vecItem.size() + item->GetItemNum() >= m_maxItemNum)
	{
		L_DEBUG("container item is too max. %d+%d>= %d", m_vecItem.size(), item->GetItemNum(), m_maxItemNum);
		return false;
	}
	if (item->GetType() == ItemType::Container)
	{
		Container *p = dynamic_cast<Container *>(item.get());
		L_ASSERT(p);
		uint32 nestNum = 1;
		nestNum += GetNestNum();
		nestNum += p->GetSubNestNum();
		if (nestNum >= GetRootMaxNestNum())
		{
			L_DEBUG("nest too mush. %d", nestNum);
			return false;
		}
	}
	return true;
}

void Container::Remove(Item *item)
{
	for ( auto iter = m_vecItem.begin(); iter != m_vecItem.end(); ++iter)
	{
		if ((*iter).get() == item)
		{
			m_itemNum -= item->GetItemNum();
			if (m_itemNum > numeric_limits<decltype(m_itemNum)>::max() - 10000 || m_itemNum == 0)
			{
				L_ERROR("m_itemNum cal error. %d", m_itemNum);
				m_itemNum = 1;
			}
			*iter = m_vecItem.back();
			m_vecItem.erase(m_vecItem.end() - 1);
		}
	}
}

uint32 Container::GetNestNum() const
{
	uint32 num = 0;
	if (auto p = m_parent.lock())
	{
		num = p->GetNestNum() + 1;
	}
	return num;
}

uint32 Container::GetSubNestNum() const
{
	uint32 num = 0;
	for (const SItem &item : m_vecItem)
	{
		if (ItemType::Container == item->GetType())
		{
			const Container *p = dynamic_cast<const Container *>(item.get());
			L_ASSERT(p);
			uint32 t = p->GetSubNestNum()+1;
			if (t > num)
			{
				num = t;
			}
		}
	}
	return num;
}

uint32 Container::GetRootMaxNestNum() const
{
	if (auto p = m_parent.lock())
	{
		return p->GetRootMaxNestNum();
	}
	return m_maxNestNum;
}
