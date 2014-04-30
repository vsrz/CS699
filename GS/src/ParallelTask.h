#ifndef PARALLELTASK_H
#define PARALLELTASK_H

#pragma once

#include <SFML/System.hpp>
#include "State.h"

class ParallelTask
{
public:
	ParallelTask(State::Context context);
	
	void execute();
	bool isFinished();
	float getCompletion();

private:
	void runTask();

	sf::Thread mThread;
	bool mFinished;
	sf::Clock mElapsedTime;
	sf::Mutex mMutex;
	State::Context mContext;
	float mCompletion;
	float mTasks;
};

#endif
