#include "ItemMgr.h"
#include "dbStructPack.h"


void ToolItem::OnLoad(const DbItem &dbItem)
{
	Item::OnLoad(dbItem);

	L_COND_V(db::UnpackStr(m_num, dbItem.data));
}

void ToolItem::OnSave(DbItem &dbItem)
{
	Item::OnSave(dbItem);

	L_COND_V(db::PackStr(m_num, dbItem.data));

}

ToolItem::ToolItem(uint16 cfgId)
	:Item(cfgId)
{

}
