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
		ManYoung,
		ManTeen,
		WomanTeen,
		WomanMiddle,
		WomanOld,
		ManMidage,
		Count,
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

	void setNeeds(unsigned int needs);
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
	void addToPatience(sf::Time timeToAdd);
	void setPatience(float bonus = 1.f);
	void highlightCustomer();

	bool isClickable();
private:

	void initalize(const TextureManager& t, unsigned int customerType);
		
	ChairEntity* findAvailableChair(ChairEntity::Type chairType);
	ChairEntity* getOccupiedChair();
	int getNumberAvailableChairs(ChairEntity::Type chairType);

	// Random value generation
	void setNeeds();
	void setSpeed();
	
	void moveToWaitingArea();
	void moveToChair(ChairEntity* chair);
	void enterSalon();
	void checkAIState(); 
	void updatePatience(sf::Time dt);
	
	// Highlight stuff
	void updateHighlight(sf::Time dt);
	bool mHighlightCustomer;
	sf::Time mHighlightDelay;

	CustomerState mState;
	sf::Time mElapsedTime;
	sf::Time mPatienceCooldown;

	unsigned int mNeeds;
	unsigned int mType;
	float mPatience;
	float mHeight;
	bool mClickable;

	Prng rng;

	// Scoring
	float getTipAmount();
	float mPayment;
	bool mScored;

};

#endif
