#ifndef CUSTOMERSTATE_H
#define CUSTOMERSTATE_H


#pragma once
class CustomerState
{
public:
	CustomerState(void);

	enum ID
	{
		None = 0,
		EnteringSalon = 1 << 1,
		Arrived = 1 << 2,
		MovingToWaitingArea = 1 << 3,
		WaitingForService = 1 << 4,
		MovingToHaircutArea = 1 << 5,
		Haircut = 1 << 6,
		MovingToDryer = 1 << 7,
		Drier = 1 << 8,
		MovingToRegister = 1 << 9,
		WaitingToPay = 1 << 10,
		Leaving = 1 << 11,			
	};

	unsigned int getState();
	void setState(unsigned int stateId);

private:
	unsigned int mState;

};

#endif
