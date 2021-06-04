#include "PlayerMgr.h"


void PlayerDb::OnLoad(const DbPlayer &data)
{
	L_COND_V(m_data.uin == 0, "repeated load db data");
	m_data = data;
	m_tm.StartTimerSec(SAVE_INTERVAL_SEC, std::bind(&PlayerDb::OnSave, this), true);
}

void PlayerDb::OnSave()
{

}
