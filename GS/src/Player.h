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

class Player
	: public ActorEntity
{
public:
	Player(const TextureManager& textures, World* worldContext);
	Player(const TextureManager& textures, World* worldContext, unsigned int playerID);

	enum ID
	{
		None = 0,
		Manager = 1 << 0,
		ManOveralls = 2 << 0,
	};

private:

	virtual void updateCurrent(sf::Time dt);
	void initalize(const TextureManager& t);
	World* mWorld;
	bool hasReachedDestination();
	float mSpeed;
	sf::Vector2i mTilePosition;

	sf::IntRect mBoundingBox;
	
	// Animation related 
	void advanceFrame();
	void checkDirection();
	sf::Vector2f mScale;
	sf::Time mElapsedTime;

	unsigned int getCategory() const;
};

#endif
