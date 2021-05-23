#include "AccMgr.h"
#include "CfgMgr.h"
#include "def.h"
#include "EventMgr.h"
#include "CenterMgr.h"
#include "./Account/AccountMgr.h"
#include "MsgDispatch.h"

using namespace std;
using namespace su;
using namespace acc;

namespace
{
	void Start(bool &ret)
	{
		AccMgr::Ins().Start();
	}
	STATIC_RUN(RegEvent<EV_START>(Start))
}

void AccMgr::Start()
{
	L_INFO("centerAD Start");
	std::vector<Addr> vec_addr;
	Addr addr;
	addr.ip = gCfgMgr->ComCfg().access.ip;
	addr.port = gCfgMgr->ComCfg().access.port;
	vec_addr.push_back(addr);
	Init(vec_addr, CENTER_GROUP_ID, true);
}

void AccMgr::OnRegResult(uint16 svr_id)
{
	//向acc注册成功
	L_COND_V(svr_id != 0, "reg acc fail");
	L_INFO("center reg ok");
	CenterMgr::Ins().SetCenterOk();
}

void AccMgr::OnRevVerifyReq(const SessionId &id, uint32 cmd, const char *msg, uint16 msg_len)
{
	L_COND_V(CenterMgr::Ins().Allok());
	size_t len = msg_len;
	proto::Login_cs req;
	L_COND_V(proto::Unpack<proto::Login_cs>(req, msg, len));

	Account *account = AccountMgr::Ins().GetAcc(req.name);
	if (!account)
	{
		account = AccountMgr::Ins().CreateAcc(req.name);
	}
	account->ReqVerify(id, req);


	//临时 接收client请求登录消息,无条件通过，原消息号返回,
	//L_INFO("rev verfiy. cmd=%d", cmd);
	//string s(msg, msg_len);
	//string rsp_msg = "verify_ok";
	//ReqVerifyRet(id, true, cmd, rsp_msg.c_str(), rsp_msg.length());
}

void AccMgr::OnRevClientMsg(const Session &session, uint32 cmd, const char *msg, uint16 msg_len)
{
	//todo 怎么约定cmd 看具体client 协议再修改
	MsgDispatch<Session>::Ins().Dispatch(id, msg, (size_t)msg_len);
}

void AccMgr::OnClientConnect(const acc::Session &sn)
{
	Account *account = AccountMgr::Ins().GetAcc(sn.accName);
	L_COND_V(account);

	CenterSnEx *p = sn.GetEx<CenterSnEx>();
	L_COND_V(p);
	p->m_pAccount = account->GetWeakPtr();

	account->SetVerifyOk(sn.id);
}

