#include "ZoneSvrCon.h"
#include "DynCfgMgr.h"
#include "GlobalEvent.h"
#include "ZoneSvr.h"

using namespace lc;
using namespace su;
using namespace proto;





ZoneSvrCon::~ZoneSvrCon()
{
	ZoneSvrMgr::Ins().DelZoneSvr(m_svrId);
}

void ZoneSvrCon::OnRecv(const MsgPack &msg)
{
	L_DEBUG("OnRecv len=%d", msg.len);
	MsgDispatch<ZoneSvrCon>::Ins().Dispatch(*this, msg.data, msg.len);
}

void ZoneSvrCon::OnConnected()
{
	L_DEBUG("zone OnConnected, cid=%ld", GetId());

}


