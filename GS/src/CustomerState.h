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
		EnteringSalon = 1 << 0,
		Arrived = 2 << 0,
		MovingToWaitingArea = 3 << 0,
		WaitingForService = 4 << 0,
		MovingToHaircutArea = 5 << 0,
		Haircut = 6 << 0,
		MovingToDryer = 7 << 0,
		Drier = 8 << 0,
		MovingToRegister = 9 << 0,
		WaitingToPay = 10 << 0,
		Leaving = 11 << 0,			
	};

	unsigned int getState();
	void setState(unsigned int stateId);

private:
	unsigned int mState;

};

#endif
