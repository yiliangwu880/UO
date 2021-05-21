
#pragma once
#include "dbTableDef.h"
#include "AccMgr.h"
#include "MsgDispatch.h"
#include "Account.h"


class AccountMgr : public Singleton<AccountMgr>
{
	std::unordered_map<string, shared_ptr<Account> > m_name2Acc;
	//目前设计单个acc, 用cid就保证唯一了
	//cid == 0时 不插入
	std::unordered_map<uint64, shared_ptr<Account> > m_cid2Acc; 
public:
	Account *CreateAcc(const string &name);
	Account *GetAcc(const string &name);
	Account *GetAccBySid(const acc::SessionId &sid);
	void DelAcc(const string &name);
	void ChangeAccCid(Account &acc, acc::SessionId oldSid, acc::SessionId val);
private:
	void DelAccEx(const string &name);
};


