#include "NetState.h"
#include "SendToClientMgr.h"
#include "svr_util/include/str_util.h"

using namespace acc;

NetState::NetState(const Session & sn, acc::ADFacadeMgr &accMgr)
	:m_sn(sn)
	, m_accMgr(accMgr)
{
}

void NetState::Dispose()
{
	m_accMgr.DisconClient(m_sn.id);
}

void NetState::Send(Packet &packet)
{
	{//tmp log
		if (CompressionEnabled)
		{
			string str = packet.m_Stream.UnderlyingStream();
			L_DEBUG("before compile . len=%d, %s", str.length(), StrUtil::BinaryToHex(str).c_str());
		}
	}
	CStr &buffer = packet.Compile(CompressionEnabled);
	L_DEBUG("Send client len=%d, %s", buffer.length(), StrUtil::BinaryToHex(buffer).c_str());
	m_accMgr.SendToClient(m_sn.id, 0, buffer.c_str(), buffer.length());
}
