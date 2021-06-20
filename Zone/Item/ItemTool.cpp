#include "ItemMgr.h"
#include "dbStructPack.h"


void ItemTool::OnLoad(const DbItem &dbItem)
{
	Item::OnLoad(dbItem);

	L_COND_V(db::UnpackStr(m_Amount, dbItem.data));
}

void ItemTool::OnSave(DbItem &dbItem)
{
	Item::OnSave(dbItem);

	L_COND_V(db::PackStr(m_Amount, dbItem.data));

}

ItemTool::ItemTool(uint16 cfgId)
	:Item(cfgId)
{

}
