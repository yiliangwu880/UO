
#pragma once
#include "dbTableDef.h"
#include "AccMgr.h"
#include "MsgDispatch.h"
#include "Account.h"


class AccountMgr : public Singleton<AccountMgr>
{
	std::unordered_map<string, Account> m_name2Acc;
public:
	Account *CreateAcc(const string &name);
	Account *GetAcc(const string &name);
	void PostDel(const string &name);
private:
	void DelAccount(const string &name);
};


