#ifndef REGISTERQUEUE_H
#define REGISTERQUEUE_H
#pragma once

#include <queue>
#include "Customer.h"


class RegisterQueue
{
public:
	RegisterQueue();
	bool isFull();
	bool isEmpty();
	int getQueuePosition(const Customer* cust);
	bool enqueue(Customer* customer);
	void dequeue();

private:
	std::queue<Customer*> mQueue;
};

#endif
