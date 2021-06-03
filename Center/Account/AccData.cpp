#include "AccountMgr.h"
#include "db_driver.h"
#include "Player/CPlayerMgr.h"
#include "AppMgr.h"
#include <type_traits>


AccData::AccData(Account &owner, CStr &name)
	:AccountSubCom(owner)
{
	m_data.name = name;
}

void AccData::LoadDb(const DbAccount &data)
{
	m_data = data;
}

su::CStr & AccData::Name() const
{
	return m_data.name;
}

su::CStr & AccData::Psw() const
{
	return m_data.psw;
}

STATIC_RUN(db::Dbproxy::Ins().RegQueryCb(AccData::OnDbLoad));

void AccData::CreateAccount(CStr &psw)
{
	m_data.psw = psw;
	Dbproxy::Ins().Insert(m_data);
}

void AccData::OnDbLoad(bool ret, const DbAccount &data, any para)
{
	L_COND_V(!data.name.empty());
	Account *account = AccountMgr::Ins().GetAcc(data.name);
	L_COND_V(account);
	L_COND_V(data.name == account->Name());

	if (!ret)
	{
		L_INFO("load account db fail, create account %s", account->Name().c_str());
		account->m_AccData.CreateAccount(account->m_Verify.GetWaitVerifyPsw());
	}
	else
	{
		L_DEBUG("OnDbLoad ok");
		account->m_AccData.m_data = data;
	}

	account->m_Verify.OnLoadDbOk();
}


void AccData::CreateActor(const acc::Session &sn)
{
	//CenterSnEx *p = sn.GetEx<CenterSnEx>();
	//L_COND_V(p);
	//shared_ptr<Account> account = p->m_pAccount.lock();
	//L_COND_V(account);

	//if (account->m_data.vecActor.size()>= MAX_ACTOR)
	//{
	//	return;
	//}
	//DbPlayer player;
	//player.uin = 1;
	//any para = sn.id;
	//db::Dbproxy::Ins().Insert(player, para);
}

STATIC_RUN(db::Dbproxy::Ins().RegInsertCb(&AccData::OnInsert));
void AccData::OnInsert(bool ret, const DbPlayer &data, any para)
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

void AccData::SelectActor(const acc::Session &sn)
{
	//CenterSnEx *p = sn.GetEx<CenterSnEx>();
	//L_COND_V(p);
	//shared_ptr<Account> account = p->m_pAccount.lock();
	//L_COND_V(account);

	////if no player exit
	//DbPlayer data;
	//data.uin = 1;
	//any para = sn.id;
	//db::Dbproxy::Ins().Query(data, para);

}

STATIC_RUN(db::Dbproxy::Ins().RegQueryCb(&AccData::OnSelect));
void AccData::OnSelect(bool ret, const DbPlayer &data, any para)
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

