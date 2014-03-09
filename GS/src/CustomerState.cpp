#include "CustomerState.h"


CustomerState::CustomerState(void)
	: mState(ID::None)
{
}

unsigned int CustomerState::getState()
{
	return mState;
}

void CustomerState::setState(unsigned int stateId)
{
	mState = stateId;
}

