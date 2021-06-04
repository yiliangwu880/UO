#include "AccountMgr.h"



void AccSn::Dispose()
{
	AccMgr::Ins().DisconClient(sid);
}

void AccSn::Disconnect()
{
	AccMgr::Ins().DisconClient(sid);
}

void AccSn::Send(Packet &packet)
{
	{//tmp log

		L_DEBUG("send %d, %d", packet.PacketID(), packet.Length());
		if (compressionEnabled)
		{
			//string str = packet.m_Stream.UnderlyingStream();
//			L_DEBUG("before compile . len=%d, %s", str.length(), StrUtil::BinaryToHex(str).c_str());
		}
	}
	CStr &buffer = packet.Compile(compressionEnabled);
	//L_DEBUG("Send client len=%d, %s", buffer.length(), StrUtil::BinaryToHex(buffer).c_str());
	AccMgr::Ins().SendToClient(sid, 0, buffer.c_str(), buffer.length());
}


void FirstSn::Dispose()
{
	AccMgr::Ins().DisconClient(sid);
}

void FirstSn::Disconnect()
{
	AccMgr::Ins().DisconClient(sid);
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
	AccMgr::Ins().SendToClient(sid, 0, buffer.c_str(), buffer.length());
}
