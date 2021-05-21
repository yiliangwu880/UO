
#pragma once
#include "dbTableDef.h"
#include "AccMgr.h"
#include "MsgDispatch.h"

class Account
{
	enum State
	{
		None,          //��ʼ��״̬���մ���
		WaitDbQuery,   //�Ȳ����Ȩ,
		WaitAccVerify, //����ɹ�������SessionId, ��acc֪ͨ��Ȩ�ɹ���
		VerifyOk,      //��Ȩ�ɹ��������շ���Ϣ��
	};
	acc::SessionId m_waitVerifySid; //�Ȳ����Ȩ �е�sid. δ��֤����������ʧ�ܸ��ͻ���
	acc::Session m_sn;
	State m_state = None;
	db::Account m_data;
public:
	Account(const string &name);
	void ReqVerify(const acc::SessionId &id, const proto::Login_cs &req);
	void QueryAccCB(bool ret, const db::Account &data);
	const acc::SessionId &Sid() const { return m_sn.id; }
	const string &Name() const { return m_data.name; }
	void SetVerifyOk(const acc::Session &sn);
};




