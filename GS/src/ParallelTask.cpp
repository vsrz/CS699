#include "ParallelTask.h"


ParallelTask::ParallelTask(void)
	: mFinished(false)
	, mThread(&ParallelTask::runTask, this)
{

}

bool ParallelTask::isFinished()
{
	sf::Lock lock(mMutex);
	return mFinished;
}

void ParallelTask::execute()
{
	mFinished = false;
	mElapsedTime.restart();

	mThread.launch();

}

float ParallelTask::getCompletion()
{
	sf::Lock lock(mMutex);
	return mElapsedTime.getElapsedTime().asSeconds() / 0.5f;
}

void ParallelTask::runTask()
{
	// Dummy task, just stall for 5 seconds
	bool ended = false;
	while (!ended)
	{
		sf::Lock lock(mMutex); // Protect the clock
		if (mElapsedTime.getElapsedTime().asSeconds() >= 0.5f)
		{
			ended = true;
		}
	}

	// mFinished could be accessed from multiple threads
	{
		sf::Lock lock(mMutex);
		mFinished = true;
	}

}
