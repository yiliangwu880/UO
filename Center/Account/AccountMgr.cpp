#include "AccountMgr.h"
#include "db_driver.h"
#include "AppMgr.h"

using namespace proto;
using namespace acc;


namespace
{

}
Account * AccountMgr::CreateAcc(const string &name)
{
	return nullptr;
}

Account * AccountMgr::GetAcc(const string &name)
{
	return nullptr;
}

void AccountMgr::PostDel(const string &name)
{
	auto f = [name]()
	{
		AccountMgr::Ins().DelAccount(name);
	};
	AppMgr::Ins().AddPost(f);
}

void AccountMgr::DelAccount(const string &name)
{
	MapErase(m_name2Acc, name);
}
