#include "AccountMgr.h"



void AccSn::Dispose()
{
	AccMgrC::Ins().DisconClient(m_sid);
}

void AccSn::Disconnect()
{
	if (m_sid.cid == 0)return;
	AccMgrC::Ins().DisconClient(m_sid);
}

const acc::Session * AccSn::GetSn()
{
	return AccMgrC::Ins().FindSession(m_sid);
}

void AccSn::SendMessage(HueColor hue, CStr &text)
{
	UnicodeMessage msg(Serial::MinusOne, -1, MessageType::Regular, (int)hue, 3, "ENU", "System", text);
	Send(msg);
}

void AccSn::Send(Packet &packet)
{
	{//tmp log

		L_DEBUG("send 0x%x, %d", packet.PacketID(), packet.Length());
		if (compressionEnabled)
		{
			//string str = packet.m_Stream.UnderlyingStream();
//			L_DEBUG("before compile . len=%d, %s", str.length(), StrUtil::BinaryToHex(str).c_str());
		}
	}
	uint32 cmd = packet.PacketID();
	CStr &buffer = packet.Compile(compressionEnabled);
	//L_DEBUG("Send client len=%d, %s", buffer.length(), StrUtil::BinaryToHex(buffer).c_str());
	AccMgrC::Ins().SendToClient(m_sid, cmd, buffer.c_str(), buffer.length());
}


void FirstSn::Dispose()
{
	AccMgrC::Ins().DisconClient(m_sid);
}

void FirstSn::Disconnect()
{
	if (m_sid.cid == 0)return;
	AccMgrC::Ins().DisconClient(m_sid);
}

void FirstSn::Send(Packet &packet)
{
	{//tmp log
		L_DEBUG("send %d, %d", packet.PacketID(), packet.Length());
		if (compressionEnabled)
		{
			//string str = packet.m_Stream.UnderlyingStream();
			//L_DEBUG("before compile . len=%d, %s", str.length(), StrUtil::BinaryToHex(str).c_str());
		}
	}
	CStr &buffer = packet.Compile(compressionEnabled);
	//L_DEBUG("Send client len=%d, %s", buffer.length(), StrUtil::BinaryToHex(buffer).c_str());
	AccMgrC::Ins().SendToClient(m_sid, 0, buffer.c_str(), buffer.length());
}
