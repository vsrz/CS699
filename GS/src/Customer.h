#ifndef CUSTOMER_H
#define CUSTOMER_H

#pragma once
#include <array>
#include "ActorEntity.h"
#include "CustomerState.h"
#include "ChairEntity.h"

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
	
	void customerClicked();

private:

	void initalize(const TextureManager& t, unsigned int customerID);
	
	ChairEntity* findAvailableChair(ChairEntity::Type chairType);
	ChairEntity* getOccupiedChair();

	void moveToWaitingArea();
	void enterSalon();
	void checkAIState(); 

	CustomerState mState;
	sf::Time mElapsedTime;
	

};

#endif
