#include "AccountMgr.h"
#include "db_driver.h"
#include "CenterMgr.h"




void Verify::ReqVerify(const SessionId &id, CStr &psw)
{
	switch (m_state)
	{
	default:
		L_ERROR("unknow state");
		break;
	case Verify::None:
		{
			m_state = WaitAccVerify;
			m_waitVerifySid = id;
			m_waitVerifyPsw = psw;
			DbAccount acc;
			acc.name = m_owner.Name();
			db::Dbproxy::Ins().Query(acc);
			m_vtm.StartTimerSec(60, std::bind(&Verify::OnVerifyTimeOut, this));
			L_DEBUG("query db for acc");
		}
		break;
	case Verify::WaitAccVerify:
		L_INFO("refuse verify when waiting verify");
		break;
	case Verify::VerifyOk:
		{
			L_DEBUG("replace login");
			if (gTestCfg.needPsw && psw != m_owner.m_AccData.Psw())
			{
				L_INFO("wrong psw");
				return;
			}
			m_owner.m_FirstSn.Disconnect();
			m_owner.m_AccSn.Disconnect();
			SetVerifyOk(id);
		}
		break;
	}
}

void Verify::OnQueryAccFromDb()
{
	L_COND_V(WaitAccVerify == m_state || WaitReplace == m_state);

	if (gTestCfg.needPsw && m_waitVerifyPsw != m_owner.m_AccData.Psw())
	{
		L_INFO("account verify fail");
		AccountMgr::Ins().DelAcc(m_owner.Name());
		return;
	}
	m_vtm.StopTimer();
	SetVerifyOk(m_waitVerifySid);
}


void Verify::GameLogin(const acc::SessionId &sid, CStr &psw)
{
	L_COND_V(VerifyOk == m_state);
	if (gTestCfg.needPsw && psw != m_owner.m_AccData.Psw())
	{
		L_ERROR("err psw");
		return;
	}
	VerifyRetStruct d;
	d.is_success = true;
	d.accName = m_owner.Name();
	AccMgr::Ins().ReqVerifyRet(sid, d);
}

void Verify::OnClientConFor2nd(const acc::SessionId &sid)
{
	L_DEBUG("game login ok");
	L_COND_V(VerifyOk == m_state);
	m_owner.m_AccSn.SetSessionId(sid);

	// 接受登录
	//state.CityInfo = e.CityInfo;
	SupportedFeatures sf;
	m_owner.Send(sf);

	//if (state.NewCharacterList)
	//{
	CharacterList cl(m_owner);
	m_owner.Send(cl);
	//}
	//else
	//{
	//	m_owner.Send(new CharacterListOld(state.Account, state.CityInfo));
	//}
}

void Verify::SetVerifyOk(const acc::SessionId &id)
{
	m_state = VerifyOk;
	m_owner.m_FirstSn.SetSessionId(id);
	m_owner.m_FirstSn.SetCompressionEnabled(false);

	VerifyRetStruct d;
	d.is_success = true;
	AccMgr::Ins().ReqVerifyRet(id, d);

	{//send svr list 
		vector<ServerInfo> info;
		ServerInfo i;
		info.push_back(CenterMgr::Ins().GetServerInfo());
		AccountLoginAck rsp(info);
		m_owner.m_FirstSn.Send(rsp);
	}
}

void Verify::OnVerifyTimeOut()
{
	L_DEBUG("OnVerifyTimeOut %s", m_owner.Name().c_str());
	AccountMgr::Ins().DelAcc(m_owner.Name());
}
