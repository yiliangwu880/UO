#include "AccountMgr.h"
#include "db_driver.h"

Verify::Verify(Account &owner)
	:AccountSubCom(owner)
{ 
}


void Verify::ReqVerify(const SessionId &id, CStr &psw)
{
	switch (m_state)
	{
	default:
		L_ERROR("unknow state");
		break;
	case Verify::None:
		{
			m_state = WaitDbQuery;
			m_waitVerifySid = id;
			m_waitVerifyPsw = psw;
			DbAccount acc;
			acc.name = m_owner.Name();
			db::Dbproxy::Ins().Query(acc);
			m_vtm.StartTimerSec(60, std::bind(&Verify::OnVerifyTimeOut, this));
		}
		break;
	case Verify::WaitDbQuery:
	case Verify::WaitAccVerify:
		L_INFO("refuse verify when waiting verify");
		break;
	case Verify::VerifyOk:
		{
			if (psw != m_owner.m_AccData.Psw())
			{
				return;
			}
			m_state = WaitReplace;
			AccMgr::Ins().DisconClient(m_owner.m_AccData.GetSid());
			VerifyRetStruct d;
			AccMgr::Ins().ReqVerifyRet(id, d);
		}
		break;
	}
}

void Verify::OnDbLoad()
{
	L_COND_V(WaitDbQuery == m_state);
	if (m_waitVerifyPsw != m_owner.m_AccData.Psw())
	{
		L_INFO("account verify fail");
		AccountMgr::Ins().DelAcc(m_owner.Name());
		return;
	}
	m_state = WaitAccVerify;
	VerifyRetStruct d;
	AccMgr::Ins().ReqVerifyRet(m_waitVerifySid, d);
}

void Verify::SetVerifyOk(const acc::SessionId &sid)
{
	L_COND_V(WaitAccVerify == m_state || WaitReplace == m_state);
	m_vtm.StopTimer();
	m_state = VerifyOk;
	m_owner.m_AccData.SetSid(sid);
}

void Verify::OnVerifyTimeOut()
{
	L_DEBUG("OnVerifyTimeOut %s", m_owner.Name().c_str());
	AccountMgr::Ins().DelAcc(m_owner.Name());
}
