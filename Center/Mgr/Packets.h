#pragma once
#include "SendToClientMgr.h"

struct ServerInfo
{
	string Name;

	int FullPercent=0;

	int TimeZone=0;

	uint32 Address;

	ServerInfo() {};
	ServerInfo(string name, int fullPercent, int tz, uint32 address)
	{
		Name = name;
		FullPercent = fullPercent;
		TimeZone = 0; //tz.GetUtcOffset(DateTime.Now).Hours;
		Address = address;
	}
};

class AccountLoginAck : public Packet
{
public:
	 AccountLoginAck(const vector<ServerInfo> &info)
		: Packet(0xA8)
	{
		EnsureCapacity(6 + (info.size() * 40));

		m_Stream.Write((byte)0x5D); // Unknown

		m_Stream.Write((ushort)info.size());

		for (int i = 0; i < (int)info.size(); ++i)
		{
			ServerInfo si = info[i];

			m_Stream.Write((ushort)i);
			m_Stream.WriteAsciiFixed(si.Name, 32);
			m_Stream.Write((byte)si.FullPercent);
			m_Stream.Write((sbyte)si.TimeZone);
			m_Stream.Write(si.Address);//(Utility.GetAddressValue(si.Address.Address));
		}
	}
};