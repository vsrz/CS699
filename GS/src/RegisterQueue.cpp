#include "RegisterQueue.h"
#include "Glob.h"

RegisterQueue::RegisterQueue()
{

}

bool RegisterQueue::isFull()
{
	return mQueue.size() == Config::RegisterQueue::SIZE;
}

bool RegisterQueue::isEmpty()
{
	return mQueue.size() == 0;
}

// Returns the tile position where they will land in the queue
bool RegisterQueue::enqueue(Customer* customer)
{
	if (!isFull())
	{
		mQueue.push(customer);
		customer->moveToTile(Config::RegisterQueue::POSITION[mQueue.size()-1]);
		return true;
	}
	return false;
}


int RegisterQueue::getQueuePosition(const Customer* cust)
{
	std::queue<Customer*> line = mQueue;

	for (size_t i = 0; i < line.size(); i++)
	{
		Customer* c = line.front();
		if (c == cust)
		{
			return i;
		}
		line.pop();
	}
	return -1;
}

// Remove a customer from the queue, and move everyone up one position
void RegisterQueue::dequeue()
{
	Customer* cust = mQueue.front();

	// Make sure you aren't paid for people who bail
	if (cust->getState() == CustomerState::WaitingToPay)
	{
		cust->leaveStore();
	}
	mQueue.pop();
	std::queue<Customer*> line;
	
	size_t size = mQueue.size();
	// For each customer in line, move them up the line one position
	for (size_t i = 0; i < size; i++)
	{
		Customer* c = mQueue.front();
		if (c->getState() != CustomerState::WaitingToPay)
		{
			mQueue.pop();
			continue;
		}
		c->moveToTile(Config::RegisterQueue::POSITION[i]);
		line.push(c);
		mQueue.pop();
	}
	mQueue = line;
}

