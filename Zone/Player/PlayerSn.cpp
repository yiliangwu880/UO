#include "PlayerMgr.h"


bool PlayerSn::Reset(uint64 cid)
{
	const Session *sn = AccMgr::Ins().FindSessionByCid(cid);
	ZoneSnEx *pZoneSnEx = sn->GetEx<ZoneSnEx>();
	L_COND(pZoneSnEx, false);
	pZoneSnEx->m_pPlayer = m_owner;

	m_sid.cid = cid;
	m_ns.Init(*sn);
	return true;
}

void PlayerSn::Send(Packet &packet)
{
	{//tmp log

		L_DEBUG("send 0x%x, %d", (uint32)packet.PacketID(), packet.Length());
		string str = packet.m_Stream.UnderlyingStream();
		L_DEBUG("before compile . len=%d, %s", str.length(), StrUtil::BinaryToHex(str).c_str());
	}
	CStr &buffer = packet.Compile(true);
	//L_DEBUG("Send client len=%d, %s", buffer.length(), StrUtil::BinaryToHex(buffer).c_str());
	AccMgr::Ins().SendToClient(m_sid, 0, buffer.c_str(), buffer.length());
}


void PlayerSn::Dispose()
{
	AccMgr::Ins().DisconClient(m_sid);
}

void PlayerSn::Disconnect()
{
	AccMgr::Ins().DisconClient(m_sid);
}