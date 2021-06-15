#include "ItemMgr.h"
#include "dbStructPack.h"

void Weapon::OnLoad(const DbItem &dbItem)
{
	Item::OnLoad(dbItem);

	L_COND_V(db::UnpackStr(m_dbEquipItem, dbItem.data));
}

void Weapon::OnSave(DbItem &dbItem)
{
	Item::OnSave(dbItem);

	L_COND_V(db::PackStr(m_dbEquipItem, dbItem.data));

}

Weapon::Weapon(uint16 cfgId)
	:Item(cfgId)
{
	m_cfg = gCfg.GetWeaponCfg(cfgId);
	if (m_cfg == nullptr)
	{
		L_ERROR("find cfg fail %d", cfgId);
		return;
	}
}
