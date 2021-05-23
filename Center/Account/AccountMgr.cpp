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


void AccountMgr::DelAcc(const string &name)
{
	auto f = [name]()
	{
		AccountMgr::Ins().DelAccEx(name);
	};
	AppMgr::Ins().AddPost(f);
}

void AccountMgr::DelAccEx(const string &name)
{
	auto it = m_name2Acc.find(name);
	if (it == m_name2Acc.end())
	{
		L_ERROR("del fail");
		return;
	}
	m_name2Acc.erase(it);
}
