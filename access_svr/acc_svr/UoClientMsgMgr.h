//UO项目特有，为了根据ID 获取包 长度
#pragma once
#include "AccMgr.h"
#include <numeric>


struct PacketHandler
{
	int m_PacketID=0;
	int m_Length=0;
	PacketHandler() {};
	PacketHandler(int packetID, int length, bool ingame)
	{
		m_PacketID = packetID;
		m_Length = length;
	}
};

class PacketHandlers : public Singleton<PacketHandlers>
{
	std::vector<PacketHandler> m_Handlers;
	
public:
	void Init();
	//@length 包固定长度。 0表示包是可变长度
	void Register(uint8_t packetID, int length, bool ingame);		
	//猜测和 6017 客户端版本有关，先和Register相同处理
	void Register6017(int packetID, int length, bool ingame) { Register(packetID, length, ingame); };
	void RegisterExtended(int packetID, bool ingame) { };
	void RegisterEncoded(int packetID, bool ingame) { };
	PacketHandler *GetHandler(uint8_t packetID);
	const std::vector<PacketHandler> &GetHandlers()const  { return m_Handlers; };

};
