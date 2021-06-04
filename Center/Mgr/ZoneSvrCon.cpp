#include "ZoneSvrCon.h"
#include "CfgMgr.h"
#include "EventMgr.h"

using namespace lc;
using namespace su;
using namespace proto;





void ZoneSvrCon::OnRecv(const MsgPack &msg)
{
	L_DEBUG("OnRecv len=%d", msg.len);
	MsgDispatch<ZoneSvrCon>::Ins().Dispatch(*this, msg.data, msg.len);
}

void ZoneSvrCon::OnConnected()
{
	L_DEBUG("zone OnConnected, cid=%ld", GetId());

}


