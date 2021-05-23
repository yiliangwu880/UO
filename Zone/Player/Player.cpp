#include "Player.h"

void PlayerScene::SetState(State val)
{
	State(val);
	if (State::Playing == State())
	{
		//resume msg
	}
	else if (State::Moving == State())
	{
		//pause msg
	}
}
