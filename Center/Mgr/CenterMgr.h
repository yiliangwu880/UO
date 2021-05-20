//所有服务管理

#pragma once



class CenterMgr : public Singleton<CenterMgr>
{
	bool m_allok = false; //true 表示所有服务器链接准备好，可以登录游戏
	bool m_isCenterOk = false;
	std::unordered_map<uint16, bool> m_zoneId2Ok;

public:
	void Init();
	bool Allok() const { return m_allok; }
	void SetCenterOk();
	void SetZoneOk(uint16 svrId);

private:
	void checkAllOk();
};
