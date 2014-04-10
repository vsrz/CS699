/**
 *	ActorEntity.h
 *	An Actor is a game object that is movable. It also implements animation
 *	features.
 **/


#ifndef ACTORENTITY_H
#define ACTORENTITY_H

#pragma once

#include <SFML/Graphics.hpp>
#include <stack>
#include <queue>
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "Glob.h"

class World;
class ChairEntity;

class ActorEntity
	: public Entity
{
public:
	typedef std::queue<TilePosition> Path;
	explicit ActorEntity(World* world);
	virtual ~ActorEntity();
	void setTravelPath(Path travelPath);	
	
	void moveToTile(TilePosition tilePosition);
	void moveToTile(Path path);
	
	Direction getDirection();
	void setDirection(Direction d);

	void sit(ChairEntity* chair);
	void stand(ChairEntity* chair);
	bool isSitting();
	
	void setSpeed(float speed);
	float getSpeed();
	bool isMoving();
protected:

	Direction mDirection;
	void checkDirection();

	void update(sf::Time dt);
	sf::Time mElapsedTime;

	Path mTravelPath;
	TilePosition mTileDestination;
	SpritePosition mSpriteDestination;
	void advanceFrame();
	sf::Vector2i mFrameSize;
	std::size_t mFrame;
	std::size_t mNumFrames;
	std::size_t mFrameOffset;
	bool mSitting;

	bool hasReachedDestination();

private:
	void updateTilemap(sf::Vector2f c, sf::Vector2f n);

	Path findPath(TilePosition destination);
	sf::Vector2f moveSprite(SpritePosition currentPosition, SpritePosition destPosition);
	float mSpeed;

};

#endif
