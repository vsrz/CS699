#include "PlayerState.h"


PlayerState::PlayerState(void)
{
	mState = 0;
}

unsigned int PlayerState::getState()
{
	return mState;
}

void PlayerState::setState(unsigned int state)
{
	mState = state;
}