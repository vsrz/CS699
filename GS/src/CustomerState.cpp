#include "CustomerState.h"
#include <iostream>
CustomerState::CustomerState(void)
	: mState(ID::None)
{
	mClock.restart();
}

unsigned int CustomerState::getState()
{
	return mState;
}

void CustomerState::setState(unsigned int stateId)
{
	mState = stateId;	
	mLastStateChange = mClock.getElapsedTime();
	mClock.restart();
}

sf::Time CustomerState::getLastStateChange()
{
	return mLastStateChange;
}