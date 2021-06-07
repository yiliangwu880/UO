#include "PlayerMgr.h"
#include "db_driver.h"


void PlayerDb::OnLoad(const DbPlayer &data)
{
	L_COND_V(m_data.uin == 0, "repeated load db data");
	m_data = data;
	m_tm.StartTimerSec(SAVE_INTERVAL_SEC, std::bind(&PlayerDb::OnSave, this), true);
	m_owner.FireEvent<EV_LOAD_DB>(m_data);
}

void PlayerDb::OnSave()
{
	m_owner.FireEvent<EV_SAVE_DB>(m_data);
	Dbproxy::Ins().Insert(m_data);
}
