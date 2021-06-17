#include "NetState.h"
#include "PacketsBase.h"
#include "svr_util/include/str_util.h"
#include "Player/PlayerMgr.h"

using namespace acc;

NetState::NetState(const Session & sn)
	:m_sn(&sn)
	, m_accMgr(AccMgr::Ins())
{
}

NetState::NetState()
	:m_accMgr(AccMgr::Ins())
{

}

void NetState::Init(const acc::Session & sn)
{
	m_sn = &sn;
}

void NetState::Dispose()
{
	m_accMgr.DisconClient(m_sn->id);
}

void NetState::Send(Packet &packet)
{
	if (gDynCfg.ComCfg().testCfg.isSendLog)
	{//tmp log
		if (CompressionEnabled)
		{
			string str = packet.m_Stream.UnderlyingStream();
			L_DEBUG("len=%d, %s", str.length(), StrUtil::BinaryToHex(str).c_str());
		}
	}
	CStr &buffer = packet.Compile(CompressionEnabled);
//	L_DEBUG("Send client len=%d, %s", buffer.length(), StrUtil::BinaryToHex(buffer).c_str());
	m_accMgr.SendToClient(m_sn->id, 0, buffer.c_str(), buffer.length());
}



std::shared_ptr<Player> NetState::GetPlayer()
{
	ZoneSnEx *p = m_sn->GetEx<ZoneSnEx>();
	L_COND(p, nullptr);
	shared_ptr<Player> player = p->m_pPlayer.lock();
	return player;
}

Actor *NetState::Mobile()
{
	ZoneSnEx *p = m_sn->GetEx<ZoneSnEx>();
	L_COND(p, nullptr);
	shared_ptr<Player> player = p->m_pPlayer.lock();
	return &(player->m_Actor);
}
