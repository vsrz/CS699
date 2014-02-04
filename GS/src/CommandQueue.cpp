#include "CommandQueue.h"

void CommandQueue::push(const Command& command)
{
	mQueue.push(command);
}

Command CommandQueue::pop()
{
	Command c = mQueue.front();
	mQueue.pop();
	return c;
}

bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}

