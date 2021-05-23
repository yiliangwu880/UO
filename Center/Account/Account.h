
#pragma once
#include "dbTableDef.h"
#include "AccMgr.h"
#include "MsgDispatch.h"

class Account : public WeakPtr<Account>
{
	static const int MAX_ACTOR = 4;
	enum State
	{
		None,          //��ʼ��״̬���մ���
		WaitDbQuery,   //�Ȳ����Ȩ,
		WaitAccVerify, //����ɹ��� ��acc֪ͨ��Ȩ�ɹ���
		VerifyOk,      //��Ȩ�ɹ��������շ���Ϣ�� ����������֤ͨ����--��WaitReplace
		WaitReplace,   //���ż���ɹ��� ��acc֪ͨ��Ȩ�ɹ���
	};

	State m_state = None;
	acc::SessionId m_waitVerifySid; //�Ȳ����Ȩ �е�sid. δ��֤����������ʧ�ܸ��ͻ���
	string m_waitVerfyPsw;
	acc::SessionId m_sid;
	db::Account m_data;

public:
	Account(const string &name);
	void ReqVerify(const acc::SessionId &id, const proto::Login_cs &req);
	void OnDbLoad(bool ret, const db::Account &data);
	const acc::SessionId &Sid() const { return m_sid.id; }
	const string &Name() const { return m_data.name; }
	void SetVerifyOk(const acc::SessionId &sid);

	static void CreateActor(acc::Session &sn, const proto::CreateActor_cs &msg);
	static void OnInsert(bool ret, const db::Player &data, any para);

	static void SelectActor(acc::Session &sn, const proto::SelectActor_cs &msg);
	static void OnSelect(bool ret, const db::Player &data, any para);
};




