#ifndef REGISTERQUEUE_H
#define REGISTERQUEUE_H
#pragma once

#include <queue>
#include "Customer.h"


class RegisterQueue
{
public:
	RegisterQueue();
	bool isQueueFull();
	int getQueuePosition(const Customer* cust);
	bool enqueue(Customer* customer);
	Customer* dequeue();
private:
	std::queue<Customer*> mQueue;
};

#endif
