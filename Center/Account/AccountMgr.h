
#pragma once
#include "dbTableDef.h"
#include "AccMgr.h"
#include "MsgDispatch.h"
#include "Account.h"


class AccountMgr : public Singleton<AccountMgr>
{
	std::unordered_map<string, shared_ptr<Account> > m_name2Acc;
	//Ŀǰ��Ƶ���acc, ��cid�ͱ�֤Ψһ��
	//cid == 0ʱ ������
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


