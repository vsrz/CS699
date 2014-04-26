#ifndef CUSTOMERSTATE_H
#define CUSTOMERSTATE_H

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#pragma once
class CustomerState
{
public:
	CustomerState(void);

	enum ID
	{
		None ,
		EnteringSalon,
		Arrived,
		MovingToWaitingArea,
		
		WaitingForService,
		MovingToWashingArea,
		WaitingForWashService,
		
		WaitingToMoveToHaircutArea,
		MovingToHaircutArea,
		WaitingForHaircutService,
		
		WaitingToMoveToColorArea,
		MovingToColorArea,
		WaitingForColorService,
		
		MovingToRegister,
		WaitingToPay,
		Leaving,
		
		Delete,
	};

	unsigned int getState();
	void setState(unsigned int stateId);

	sf::Time getLastStateChange();

private:
	unsigned int mState;
	sf::Clock mClock;

	// The last time that this customer has been interacted with
	sf::Time mLastStateChange;

};

#endif
