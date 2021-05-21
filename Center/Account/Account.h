
#pragma once
#include "dbTableDef.h"
#include "AccMgr.h"
#include "MsgDispatch.h"

class Account
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
	acc::Session m_sn;
	db::Account m_data;

public:
	Account(const string &name);
	void ReqVerify(const acc::SessionId &id, const proto::Login_cs &req);
	void OnDbLoad(bool ret, const db::Account &data);
	const acc::SessionId &Sid() const { return m_sn.id; }
	const string &Name() const { return m_data.name; }
	void SetVerifyOk(const acc::Session &sn);

	static void CreateActor(acc::SessionId &sid, const proto::CreateActor_cs &msg);
};




