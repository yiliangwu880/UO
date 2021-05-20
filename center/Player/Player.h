#pragma once

class SceneTran
{
	enum class State
	{
		Playing,
		Moving,
	};
	State m_State;

public:
	State GetState() const { return m_State; }
	void SetState(State val);
};

class Player
{
	uint64 uin=0;

public:
	Player() {};
	Player(Player&&) {}; //移动构造函数,为了支持map创建 Player

	void Init(uint64 uin) {};

	template<class Msg>
	bool SendToZone(const Msg &msg)
	{
		return false;
	}
private:

};

