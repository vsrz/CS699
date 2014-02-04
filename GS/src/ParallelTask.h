#ifndef PARALLELTASK_H
#define PARALLELTASK_H

#pragma once

#include <SFML/System.hpp>

class ParallelTask
{
public:
	ParallelTask(void);
	
	void execute();
	bool isFinished();
	float getCompletion();

private:
	void runTask();

	sf::Thread mThread;
	bool mFinished;
	sf::Clock mElapsedTime;
	sf::Mutex mMutex;
};

#endif
