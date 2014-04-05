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
		EnteringSalon,
		Arrived,
		MovingToWaitingArea,
		WaitingForService,
		MovingToWashingArea,
		WaitingForWashService,
		MovingToHaircutArea,
		WaitingForHaircutService,
		MovingToDryer,
		Drier,
		MovingToRegister,
		WaitingToPay,
		Leaving,
	};

	unsigned int getState();
	void setState(unsigned int stateId);

private:
	unsigned int mState;

};

#endif
