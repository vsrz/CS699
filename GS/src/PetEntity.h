#ifndef PETENTITY_H
#define PETENTITY_H

#pragma once

#include "Glob.h"
#include "ActorEntity.h"


class World;

class PetEntity :
	public ActorEntity
{
public:
	PetEntity(const TextureManager& textures, World* world);

private:
	enum State
	{
		Idle,
		Random,
		FollowingManager,
		Consumption,
		GoingToSleep,
		Sleeping,
		FindingPlayer,
	};
	void initalize(const TextureManager& t);
	
	TilePosition moveNearPlayer();
	TilePosition findNearestAdjacentTile(TilePosition tile);
	TilePosition randomTile();
	void checkProximity();
	

	void sleep();
	int mIrritation;
	State mState;
	sf::Time mElapsedTime;

	
	void updateState();
	void updateCurrent(sf::Time dt);
};

#endif
