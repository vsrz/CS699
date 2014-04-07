#include "RegisterQueue.h"
#include "Glob.h"

RegisterQueue::RegisterQueue()
{

}

bool RegisterQueue::isQueueFull()
{
	return mQueue.size() == 8;
}

// Returns the tile position where they will land in the queue
bool RegisterQueue::enqueue(Customer* customer)
{
	if (!isQueueFull())
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
	
	for (int i = 0; i < line.size(); i++)
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
Customer* RegisterQueue::dequeue()
{
	Customer* cust = mQueue.front();
	mQueue.pop();
	std::queue<Customer*> line;
	
	// For each customer in line, move them up the line one position
	for (int i = 0; i < mQueue.size(); i++)
	{
		Customer* c = mQueue.front();
		c->moveToTile(Config::RegisterQueue::POSITION[i]);
		line.push(c);
		mQueue.pop();
	}
	mQueue = line;
	return cust;
}

