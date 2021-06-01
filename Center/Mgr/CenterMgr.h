//所有服务管理

#pragma once


struct ServerAddr
{
	int Address=0;
	uint16 Port = 0;
};
struct ServerInfo
{
	string Name = "Endless Of Journey";
	int FullPercent = 0;
	int TimeZone = 8;
	ServerAddr Address;
};

class CenterMgr : public Singleton<CenterMgr>
{
	bool m_allok = false; //true 表示所有服务器链接准备好，可以登录游戏
	bool m_isCenterOk = false;
	std::unordered_map<uint16, bool> m_zoneId2Ok;
	ServerInfo m_ServerInfo;
public:
	void Init();
	bool Allok() const { return m_allok; }
	void SetCenterOk();
	void SetZoneOk(uint16 svrId);
	const ServerInfo &GetServerInfo() { return m_ServerInfo; }
private:
	void checkAllOk();
};
