#include "db_driver.h"
#include "connect.h"
#include "log_def.h"

using namespace std;
using namespace lc;
using namespace su;
using namespace db;

static const uint32 RE_CON_INTERVAL_SEC = 10; //x�볢������

void DbClientCon::OnRecv(const lc::MsgPack &msg_pack)
{
	Dbproxy::Ins().OnRecv(msg_pack);
}

void db::DbClientCon::OnTryReconTimeOut()
{
	TryReconnect();
}

void DbClientCon::OnConnected()
{
	if (Dbproxy::Ins().m_conCb)
	{
		Dbproxy::Ins().m_conCb();
	}
}

void DbClientCon::OnDisconnected()
{
	L_DEBUG("start try recon timer , sec=%d", RE_CON_INTERVAL_SEC);
	auto f = std::bind(&DbClientCon::OnTryReconTimeOut, this);
	m_recon_tm.StopTimer();
	m_recon_tm.StartTimerSec(RE_CON_INTERVAL_SEC, f);
}


