#include "AccountMgr.h"
#include "db_driver.h"
#include "AppMgr.h"

using namespace proto;
using namespace acc;


namespace
{

}
Account &AccountMgr::DoGetAcc(const string &name)
{
	auto it = m_name2Acc.find(name);
	if (it != m_name2Acc.end())
	{
		return *it->second;
	}


	Account *pAcc = new Account(name);
	m_name2Acc[name] = pAcc;
	return *pAcc;
}

Account *AccountMgr::GetAcc(const string &name)
{
	auto it = m_name2Acc.find(name);
	if (it != m_name2Acc.end())
	{
		return it->second;
	}

	return nullptr;
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
	delete it->second;
	m_name2Acc.erase(it);
}
