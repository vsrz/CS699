#ifndef CUSTOMERSTATE_H
#define CUSTOMERSTATE_H


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
		MovingToDryer,
		Drier,
		MovingToRegister,
		WaitingToPay,
		Leaving,
		Delete,
	};

	unsigned int getState();
	void setState(unsigned int stateId);

private:
	unsigned int mState;

};

#endif
