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
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "Glob.h"

class World;

class ActorEntity
	: public Entity
{
public:
	explicit ActorEntity(World* world);
	virtual ~ActorEntity();
	void setTravelPath(std::stack<TilePosition> travelPath);	
	
	void moveToTile(TilePosition tilePosition);
	void moveToTile(std::stack<TilePosition> path);

	void setSpeed(float speed);
	float getSpeed();
	bool isMoving();
protected:
	enum Direction
	{
		None = 0,
		South = 1 << 1,
		North = 1 << 2,
		West = 1 << 3,
		East = 1 << 4,
	};

	
	unsigned int mDirection;
	void checkDirection();

	void update(sf::Time dt);
	sf::Time mElapsedTime;

	std::stack<TilePosition> mTravelPath;
	TilePosition mTileDestination;
	SpritePosition mSpriteDestination;
	void advanceFrame();
	sf::Vector2i mFrameSize;
	std::size_t mFrame;
	std::size_t mNumFrames;
	std::size_t mFrameOffset;

	bool hasReachedDestination();

private:
	void updateTilemap(sf::Vector2f c, sf::Vector2f n);

	std::stack<TilePosition> findPath(TilePosition destination);
	sf::Vector2f moveSprite(SpritePosition currentPosition, SpritePosition destPosition);
	float mSpeed;

};

#endif
