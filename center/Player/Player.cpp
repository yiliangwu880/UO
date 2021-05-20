#include "Player.h"

void SceneTran::SetState(State val)
{
	m_State = val;
	if (State::Playing == m_State)
	{
		//resume msg
	}
	else if (State::Moving == m_State)
	{
		//pause msg
	}
}
