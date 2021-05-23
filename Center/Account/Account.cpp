#include "Account.h"
#include "AccountMgr.h"
#include "db_driver.h"
#include "AppMgr.h"

using namespace proto;
using namespace acc;


namespace
{
	void OnDbLoad(bool ret, const db::Account &data, any para)
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
			AccMgr::Ins().DisconClient(m_sid);
			VerifyRetStruct d;
			d.accName = m_data.name;
			//d.msg = ntf to client login ok
			AccMgr::Ins().ReqVerifyRet(id, d);
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
	VerifyRetStruct d;
	d.accName = m_data.name;
	//d.msg = ntf to client login ok
	AccMgr::Ins().ReqVerifyRet(m_waitVerifySid, d);
}

void Account::SetVerifyOk(const acc::SessionId &sid)
{
	L_COND_V(WaitAccVerify == m_state || WaitReplace == m_state);
	m_state = VerifyOk;
	m_sid = sid;
}



STATIC_RUN(MsgDispatch<Session>::Ins().RegMsgHandler(&Account::CreateActor));
void Account::CreateActor(acc::Session &sn, const proto::CreateActor_cs &msg)
{
	CenterSnEx *p = sn.GetEx<CenterSnEx>();
	L_COND_V(p);
	shared_ptr<Account> account = p->m_pAccount.lock();
	L_COND_V(account);

	if (account->m_data.vecActor.size()>= MAX_ACTOR)
	{
		return;
	}
	db::Player player;
	player.uin = 1;
	any para = sn.id;
	db::Dbproxy::Ins().Insert(player, para);
}

STATIC_RUN(db::Dbproxy::Ins().RegInsertCb(OnInsert));
void Account::OnInsert(bool ret, const db::Player &data, any para) //需要做 响应 session id. 考虑设db有sid.
{
	SessionId *sid = para._Cast<SessionId>();
	L_COND_V(sid);
	L_COND_V(ret);
	Player *player = PlayerMgr::Ins().CreatePlayer(data.uin);
	L_COND_V(player);

	const Session *sn= AccMgr::Ins().FindSession(*sid);

	CenterSnEx *p = sn->GetEx<CenterSnEx>();
	L_COND_V(p);
	p->m_pAccount.reset();
	p->m_pPlayer = player->GetWeakPtr();

	player->SetSid(sn.id);

	//AccMgr::Ins().BroadcastUinToSession(*sid, data.uin); //不需要了。 zone创建player,根据sid 查找sn,关联起来
}
