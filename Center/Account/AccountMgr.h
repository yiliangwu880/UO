
#pragma once
#include "dbTableDef.h"
#include "AccMgrC.h"
#include "MsgDispatch.h"
#include "Account.h"
#include "DynCfgMgr.h"


class AccountMgr : public Singleton<AccountMgr>
{ 
	std::unordered_map<string, Account *> m_name2Acc;
public:
	//或者ACC，没有就创建个新的
	Account &DoGetAcc(const string &name);
	Account *GetAcc(const string &name);
	void DelAcc(const string &name);
private:
	void DelAccEx(const string &name);
};


