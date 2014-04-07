#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#pragma once
class PlayerState
{
public:
	PlayerState(void);
	enum ID
	{
		Idle,
		Walking,

	};

	unsigned int getState();
	void setState(unsigned int state);
private:
	unsigned int mState;
};

#endif
