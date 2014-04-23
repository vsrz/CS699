#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <SFML/Window.hpp>
#include <map>
#include <math.h>
#include <iostream>
#include <stack>
#include "ResourceIdentifiers.h"
#include "Pathfinder.h"
#include "ActorEntity.h"

class World;
class RegisterQueue;
class ChairEntity;
class Customer;

class Player
	: public ActorEntity
{
public:
	Player(const TextureManager& textures, World* worldContext);
	Player(const TextureManager& textures, World* worldContext, unsigned int playerID);

	enum State
	{
		Idle,
		Walking,
		Busy,
	};

	enum Action
	{
		None,
		UsingRegister,
		WashingHair,
		CuttingHair,
		ColoringHair,
	};

	unsigned int getState();
	void setState(unsigned int state);
	void setBusy(sf::Time seconds);
	unsigned int getCurrentAction();

	// Action methods
	void useRegister(RegisterQueue* queue);
	void useStation(ChairEntity* chair);
private:

	virtual void updateCurrent(sf::Time dt);
	void initalize(const TextureManager& t);
	World* mWorld;
	bool hasReachedDestination();
	TilePosition mTilePosition;

	sf::IntRect mBoundingBox;
	unsigned int mState;
	unsigned int mCurrentAction;

	// Pointer to the register queue for processing customers
	RegisterQueue *mRegisterQueue;

	// The customer we are working on right now
	Customer* mCurrentCustomer;

	
	// Animation related 
	void advanceFrame();
	void checkDirection();
	sf::Vector2f mScale;
	sf::Time mElapsedTime;
	sf::Time mBusyTime, mBusyElapsed;
	
	unsigned int getCategory() const;
};

#endif
