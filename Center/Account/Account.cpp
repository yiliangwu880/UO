#include "Account.h"
#include "AccountMgr.h"
#include "db_driver.h"
#include "AppMgr.h"

using namespace proto;
using namespace acc;


namespace
{
	void OnDbLoad(bool ret, const db::Account &data)
	{
		L_COND_V(!data.name.empty());
		Account *account = AccountMgr::Ins().GetAcc(data.name);
		L_COND_V(account);
		account->OnDbLoad(ret, data);
	}
	STATIC_RUN(db::Dbproxy::Ins().RegQueryCb(OnDbLoad));


}


Account::Account(const string &name)
{
	m_data.name = name;
}

void Account::ReqVerify(const SessionId &id, const Login_cs &req)
{
	switch (m_state)
	{
	default:
		L_ERROR("unknow state");
		break;
	case Account::None:
		{
			m_state = Account::WaitDbQuery;
			m_waitVerifySid = id;
			m_waitVerfyPsw = req.psw;
			db::Account acc;
			acc.name == req.name;
			db::Dbproxy::Ins().Query(acc);
		}
		break;
	case Account::WaitDbQuery:
	case Account::WaitAccVerify:
		L_INFO("refuse verify when waiting verify");
		break;
	case Account::VerifyOk:
		{
			if (req.psw != m_data.psw)
			{
				return;
			}
			m_state = WaitReplace;
			SessionId newId;
			AccountMgr::Ins().ChangeAccCid(*this, m_sn.id, newId);
			m_sn.Clear();
			//return ok
		}
		break;
	}

}

void Account::OnDbLoad(bool ret, const db::Account &data)
{
	L_COND_V(Account::WaitDbQuery == m_state);
	L_COND_V(data.name == m_data.name);
	if (!ret)
	{
		L_INFO("account verify fail");
		//return fail to client
		AccountMgr::Ins().DelAcc(m_data.name);
		return;
	}
	if (m_waitVerfyPsw != data.psw)
	{
		L_INFO("account verify fail");
		//return fail to client
		AccountMgr::Ins().DelAcc(m_data.name);
		return;
	}
	m_state = WaitAccVerify;
	m_data = data;

}

void Account::SetVerifyOk(const acc::Session &sn)
{
	L_COND_V(WaitAccVerify == m_state || WaitReplace == m_state);
	AccountMgr::Ins().ChangeAccCid(*this, m_sn.id, sn.id);
	m_state = VerifyOk;
	m_sn = sn;
}



void Account::CreateActor(acc::SessionId &sid, const proto::CreateActor_cs &msg)
{
	Account *p = AccountMgr::Ins().GetAccBySid(sid);
	L_COND_V(p);
	if (p->m_data.vecActor.size()>= MAX_ACTOR)
	{
		return;
	}
	db::Player player;
	player.uin = 1;
	db::Dbproxy::Ins().Insert(player);
}

STATIC_RUN(MsgDispatch<SessionId>::Ins().RegMsgHandler(&Account::CreateActor));