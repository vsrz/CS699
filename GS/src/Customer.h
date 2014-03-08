#ifndef CUSTOMER_H
#define CUSTOMER_H

#pragma once
#include "ActorEntity.h"

class World;

class Customer :
	public ActorEntity
{
public:

	enum ID
	{
		None = 0,
		Manager = 1 << 0,
		ManOveralls = 2 << 0,
	};

	Customer(const TextureManager& textures, World* world, unsigned int customerID);
	virtual void updateCurrent(sf::Time dt);

private:
	void initalize(const TextureManager& t, unsigned int customerID);
	void moveToWaitingArea();
	

};

#endif
