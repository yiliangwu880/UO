#include "Account.h"
#include "AccountMgr.h"
#include "db_driver.h"
#include "AppMgr.h"
#include "Player/CPlayerMgr.h"

using namespace proto;
using namespace acc;


namespace
{
	void OnDbLoad(bool ret, const DbAccount &data, any para)
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
			DbAccount acc;
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

void Account::OnDbLoad(bool ret, const DbAccount &data)
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


RegAccMsg(Account::CreateActor);
void Account::CreateActor(const acc::Session &sn, const proto::CreateActor_cs &msg)
{
	CenterSnEx *p = sn.GetEx<CenterSnEx>();
	L_COND_V(p);
	shared_ptr<Account> account = p->m_pAccount.lock();
	L_COND_V(account);

	if (account->m_data.vecActor.size()>= MAX_ACTOR)
	{
		return;
	}
	DbPlayer player;
	player.uin = 1;
	any para = sn.id;
	db::Dbproxy::Ins().Insert(player, para);
}
STATIC_RUN(db::Dbproxy::Ins().RegInsertCb(&Account::OnInsert));
void Account::OnInsert(bool ret, const DbPlayer &data, any para) 
{
	SessionId *sid = std::any_cast<SessionId>(&para);
	L_COND_V(sid);
	L_COND_V(ret);
	CPlayer *player = CPlayerMgr::Ins().CreatePlayer(data.uin, data.name);
	L_COND_V(player);

	const Session *sn = AccMgr::Ins().FindSession(*sid);

	CenterSnEx *p = sn->GetEx<CenterSnEx>();
	L_COND_V(p);
	p->m_pAccount.reset();
	p->m_pPlayer = player->GetWeakPtr();

	player->SetSid(sn->id);

	player->m_LoginPlayer.LoginZone(data);
}

RegAccMsg(Account::SelectActor);
void Account::SelectActor(const acc::Session &sn, const proto::SelectActor_cs &msg)
{
	CenterSnEx *p = sn.GetEx<CenterSnEx>();
	L_COND_V(p);
	shared_ptr<Account> account = p->m_pAccount.lock();
	L_COND_V(account);

	//if no player exit
	DbPlayer data;
	data.uin = 1;
	any para = sn.id;
	db::Dbproxy::Ins().Query(data, para);

}

STATIC_RUN(db::Dbproxy::Ins().RegQueryCb(&Account::OnSelect));
void Account::OnSelect(bool ret, const DbPlayer &data, any para) 
{
	SessionId *sid = std::any_cast<SessionId>(&para);
	L_COND_V(sid);
	L_COND_V(ret);
	CPlayer *player = CPlayerMgr::Ins().CreatePlayer(data.uin, data.name);
	L_COND_V(player);

	const Session *sn = AccMgr::Ins().FindSession(*sid);

	CenterSnEx *p = sn->GetEx<CenterSnEx>();
	L_COND_V(p);
	p->m_pAccount.reset();
	p->m_pPlayer = player->GetWeakPtr();

	player->SetSid(sn->id);

	player->m_LoginPlayer.LoginZone(data);
}

