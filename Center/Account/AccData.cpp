#include "AccountMgr.h"
#include "db_driver.h"
#include "Player/PlayerMgrC.h"
#include "AppMgr.h"
#include <type_traits>
#include "svr_util/include/misc.h"


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


void AccData::CreateAccount(CStr &psw)
{
	m_data.psw = psw;
	Dbproxy::Ins().Insert(m_data);
}

const std::vector<db::ActorBrief> & AccData::GetActorList()
{
	return m_data.vecActor;
}



STATIC_RUN(db::Dbproxy::Ins().RegQueryCb(AccData::OnQuery));
void AccData::OnQuery(bool ret, const DbAccount &data, any para)
{
	L_DEBUG("AccData::OnQuery");
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

	account->m_Verify.OnQueryAccFromDb();
}


//void AccData::CreateActor(const acc::Session &sn)
//{
//	//CenterSnEx *p = sn.GetEx<CenterSnEx>();
//	//L_COND_V(p);
//	//shared_ptr<Account> account = p->m_pAccount.lock();
//	//L_COND_V(account);
//
//	//if (account->m_data.vecActor.size()>= MAX_ACTOR)
//	//{
//	//	return;
//	//}
//	//DbPlayer player;
//	//player.uin = 1;
//	//any para = sn.id;
//	//db::Dbproxy::Ins().Insert(player, para);
//}

void AccData::CreatePlayer(const DbPlayer &player)
{
	if (m_data.vecActor.size() >= MAX_CHAR_NUM_IN_ACC)
	{
		//rsp fail
		return;
	}
	std::any para = m_data.name;
	Dbproxy::Ins().Insert(player, para);
}

STATIC_RUN(Dbproxy::Ins().RegInsertCb(&AccData::OnInsertPlayer));
void AccData::OnInsertPlayer(bool ret, const DbPlayer &data, any para)
{
	L_DEBUG("OnInsert player [%s]", data.name.c_str());
	string *name = std::any_cast<string>(&para);
	L_COND_V(name);
	Account *acc = AccountMgr::Ins().GetAcc(*name);
	L_COND_V(acc->IsVerify());
	if (!ret)
	{
		L_DEBUG("insert player fail. repeated uin,name=%ld [%s]", data.uin, data.name);
		static uint64 lastFailUin = 0;
		if (lastFailUin == data.uin)
		{
			L_ERROR("insert uin as name fail?");
			return;
		}
		lastFailUin = data.uin;
		DbPlayer newData = data;
		newData.name = StrNum::NumToStr(data.uin);
		Dbproxy::Ins().Insert(newData, para);
		L_DEBUG("insert player, name as uin");
		//rsp fail
		return;
	}

	///////////////////////

	acc->m_AccData.LoginPlayerByDb(data, true);
}

void AccData::LoginPlayerByDb(const DbPlayer &data, bool isCreate)
{
	PlayerC *player = PlayerMgrC::Ins().CreatePlayer(data);
	L_COND_V(player);

	const Session *sn = m_owner.m_AccSn.GetSn();
	L_COND_V(sn);
	CenterSnEx *p = sn->GetEx<CenterSnEx>();
	L_COND_V(p);
	p->m_pPlayer = *player;
	player->m_CPlayerSn.SetSid(sn->id);
	player->m_LoginPlayer.LoginZone(data, isCreate);

	if (isCreate)
	{
		ActorBrief brief;
		brief.uin = data.uin;
		brief.name = data.name;
		m_data.vecActor.push_back(brief);
		Dbproxy::Ins().Update(m_data);
	}
}

void AccData::SelectActor(uint32 idx)
{
	L_COND_V(idx < m_data.vecActor.size());

	const ActorBrief &actorBrief = m_data.vecActor[idx];
	L_COND_V(actorBrief.uin != 0);

	if (PlayerC *player = PlayerMgrC::Ins().FindPlayer(actorBrief.uin))
	{
		L_DEBUG("login player by replace");
		const Session *sn = m_owner.m_AccSn.GetSn();
		L_COND_V(sn);
		player->m_CPlayerSn.SetSid(sn->id);
		player->m_LoginPlayer.ReLogin();
	}
	else
	{
		L_DEBUG("login player by read db");
		DbPlayer d;
		d.uin = actorBrief.uin;
		std::any para = m_data.name;
		Dbproxy::Ins().Query(d, para);
	}
}

STATIC_RUN(db::Dbproxy::Ins().RegQueryCb(&AccData::OnQueryPlayer));
void AccData::OnQueryPlayer(bool ret, const DbPlayer &data, any para)
{
	L_DEBUG("OnQuery player [%s]", data.name.c_str());
	string *name = std::any_cast<string>(&para);
	L_COND_V(name);
	Account *acc = AccountMgr::Ins().GetAcc(*name);
	L_COND_V(acc->IsVerify());
	if (!ret)
	{
		L_DEBUG("OnQuery player fail.  uin,name=%ld [%s]", data.uin, data.name);
		//rsp fail
		return;
	}

	acc->m_AccData.LoginPlayerByDb(data, false);

}

