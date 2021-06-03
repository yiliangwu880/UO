
#pragma once
#include "dbTableDef.h"
#include "AccMgr.h"
#include "MsgDispatch.h"
#include "Verify.h"

//核心组件，先随便命名
class AccData : public AccountSubCom
{
	static const int MAX_ACTOR = 4;

	acc::SessionId m_sid;
	DbAccount m_data;
public:
	AccData(Account &owner, CStr &name);
	
	void LoadDb(const DbAccount &data);
	CStr &Name() const;
	CStr &Psw() const;
	const acc::SessionId &GetSid() const { return m_sid; }
	void SetSid(const acc::SessionId &id) { m_sid = id; }


	static void OnDbLoad(bool ret, const DbAccount &data, any para);
	static void OnInsert(bool ret, const DbPlayer &data, any para);
	static void OnSelect(bool ret, const DbPlayer &data, any para);
private:

	static void CreateActor(const acc::Session &sn);
	static void SelectActor(const acc::Session &sn);
};

class Account : public WeakPtr<Account>
{

public:
	Verify m_Verify;
	AccData m_AccData;

public:
	Account(const string &name);

	const string &Name() const;

private:

};




