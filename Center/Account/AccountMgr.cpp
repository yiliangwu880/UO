#include "AccountMgr.h"
#include "db_driver.h"
#include "AppMgr.h"

using namespace proto;
using namespace acc;


namespace
{

}
Account *AccountMgr::CreateAcc(const string &name)
{
	shared_ptr<Account> acc = make_shared<Account>(name);
	L_ASSERT(MapInsert(m_name2Acc, name, acc));
	return acc.get();
}

Account *AccountMgr::GetAcc(const string &name)
{
	auto *pAcc = MapFind(m_name2Acc, name);
	if (nullptr == pAcc)
	{
		return nullptr;
	}

	return (*pAcc).get();
}

Account * AccountMgr::GetAccBySid(const acc::SessionId &sid)
{
	auto *pAcc = MapFind(m_cid2Acc, sid.cid);
	if (nullptr == pAcc)
	{
		return nullptr;
	}

	return (*pAcc).get();
}

void AccountMgr::DelAcc(const string &name)
{
	auto f = [name]()
	{
		AccountMgr::Ins().DelAccEx(name);
	};
	AppMgr::Ins().AddPost(f);
}



void AccountMgr::ChangeAccCid(Account &acc, acc::SessionId oldSid, acc::SessionId newSid)
{
	if (0 != oldSid.cid)
	{
		L_ASSERT(MapErase(m_cid2Acc, oldSid.cid));
	}

	shared_ptr<Account> *pAcc = MapFind(m_name2Acc, acc.Name());

	if (0 != newSid.cid)
	{
		L_ASSERT(MapInsert(m_cid2Acc, newSid.cid, *pAcc));
	}
}



void AccountMgr::DelAccEx(const string &name)
{
	auto it = m_name2Acc.find(name);
	if (it == m_name2Acc.end())
	{
		L_ERROR("del fail");
		return;
	}
	shared_ptr<Account> acc = it->second;
	m_name2Acc.erase(it);
	m_cid2Acc.erase(acc->Sid().cid);
}
