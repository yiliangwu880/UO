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

Equip::Equip(uint16 cfgId)
	:Item(cfgId)
{
	m_cfg = gCfg.GetEquipCfg(cfgId);
	if (m_cfg == nullptr)
	{
		L_ERROR("find cfg fail %d", cfgId);
		return;
	}
}
