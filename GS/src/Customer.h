#ifndef CUSTOMER_H
#define CUSTOMER_H

#pragma once
#include <array>
#include "ActorEntity.h"
#include "CustomerState.h"
#include "ChairEntity.h"
#include "HeartEntity.h"
#include "prng.h"
class World;

class Customer :
	public ActorEntity
{
public:

	enum Type
	{
		None,
		Manager,
		ManYoung,
		ManTeen,
		ManMiddle,
		ManOld,
		WomanYoung,
		WomanTeen,
		WomanMiddle,
		WomanOld,
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
	float getPatience();
	float getHeight();
	virtual void updateCurrent(sf::Time dt);

	// Various exposed methods for directly altering the state of the customer
	unsigned int getState();
	void customerClicked();
	void leaveStore();
	bool isWaitingToMoveToStation();
	bool isReadyToDelete();
	void washHair();
	void cutHair();
	void colorHair();
	void cashOut();

private:

	void initalize(const TextureManager& t, unsigned int customerType);
		
	ChairEntity* findAvailableChair(ChairEntity::Type chairType);
	ChairEntity* getOccupiedChair();
	
	// Random value generation
	void setPatience(float bonus = 1.f);
	void setNeeds();
	void setSpeed();
	
	void moveToWaitingArea();
	void moveToChair(ChairEntity* chair);
	void enterSalon();
	void checkAIState(); 
	void updatePatience();

	CustomerState mState;
	sf::Time mElapsedTime;
	
	unsigned int mNeeds;
	unsigned int mType;
	float mPatience;
	float mHeight;

	Prng rng;

};

#endif
