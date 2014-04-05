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

	enum Type
	{
		None = 0,
		Manager = 1 << 1,
		ManYoung = 1 << 2,
		ManTeen = 1 << 3,
		ManMiddle = 1 << 4,
		ManOld = 1 << 5,
		WomanYoung = 1 << 6,
		WomanTeen = 1 << 7,
		WomanMiddle = 1 << 8,
		WomanOld = 1 << 9,
	};

	enum Needs
	{
		Invalid = 0,
		Wash = 1 << 1,
		Cut = 1 << 2,
		Color = 1 << 3,
		Dry = 1 << 4,
		Product = 1 << 5,
	};
	


	Customer(const TextureManager& textures, World* world, unsigned int customerType);
	unsigned int getNeeds();	
	virtual void updateCurrent(sf::Time dt);
	
	void customerClicked();

private:

	void initalize(const TextureManager& t, unsigned int customerType);
	
	ChairEntity* findAvailableChair(ChairEntity::Type chairType);
	ChairEntity* getOccupiedChair();
	
	// Random value generation
	void setPatience(float bonus = 0.f);
	void setNeeds();
	void setSpeed();

	void moveToWaitingArea();
	void enterSalon();
	void checkAIState(); 

	CustomerState mState;
	sf::Time mElapsedTime;
	
	unsigned int mNeeds;
	float mPatience;
};

#endif
