#include "ItemMgr.h"
#include "dbStructPack.h"

void Equip::OnLoad(const DbItem &dbItem)
{
	Item::OnLoad(dbItem);

	L_COND_V(db::UnpackStr(m_dbEquipItem, dbItem.data));
}

void Equip::OnSave(DbItem &dbItem)
{
	Item::OnSave(dbItem);

	L_COND_V(db::PackStr(m_dbEquipItem, dbItem.data));

}
