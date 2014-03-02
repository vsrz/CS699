#include "ActorEntity.h"
#include "Pathfinder.h"
#include "World.h"
#include <iostream>

ActorEntity::ActorEntity(World* world)
	: mTravelPath()
	, Entity(world)
	, mFrameSize(32.f, 64.f)
	, mFrameOffset(3)
	, mFrame(0)
	, mNumFrames(6)

{
	mSpriteDestination = mSprite.getPosition();
}

ActorEntity::~ActorEntity()
{

}

void ActorEntity::setSpeed(float speed)
{
	mSpeed = speed;
}

float ActorEntity::getSpeed()
{
	return mSpeed;
 }

void ActorEntity::update(sf::Time dt)
{

	if (!mTravelPath.empty())
	{
		mTileDestination = mTravelPath.top();
		mSpriteDestination = toSpritePosition(mTileDestination);
		sf::Vector2f currentPosition = mSprite.getPosition();
		sf::Vector2f destPosition = toSpritePosition(mTileDestination);
		sf::Vector2f movement;
		
		// If the sprite is within 5 pixels of its destination just snap it
		if (abs(destPosition.x - currentPosition.x) < 5.f)
			currentPosition.x = destPosition.x;
	
		if (abs(destPosition.y - currentPosition.y) < 5.f)
			currentPosition.y = destPosition.y;
	
		// Set the movement direction 
		if (destPosition.x > currentPosition.x)
		{
			movement.x = 1.f;
			mDirection = Direction::East;
		}
		else if (destPosition.x < currentPosition.x)
		{
			movement.x = -1.f;
			mDirection = Direction::West;
		}
		if (destPosition.y > currentPosition.y)
		{
			movement.y = 1.f;
			mDirection = Direction::South;
		}
		else if (destPosition.y < currentPosition.y)
		{
			movement.y = -1.f;
			mDirection = Direction::North;
		}

		// Update the position of the sprite on the screen
		currentPosition += movement * mSpeed;
		mSprite.setPosition(currentPosition);

		// update movement animation and direction if necessary
		if (mElapsedTime > sf::seconds(0.12f))
		{
			checkDirection();
			mElapsedTime -= sf::seconds(0.12f);
			advanceFrame();

		}
		// If this move causes the destination to be reached, remove it from the queue.
		if (hasReachedDestination())
		{
			mTravelPath.pop();
			if (mTravelPath.empty())
			{
				mFrame = 0;
			}
		}
	}
	else
	{
		// Movement complete, rest sprite
		mFrame = 0;
	}
	this->setTextureRect(
		sf::IntRect(sf::Vector2i(mFrame * mFrameSize.x, mFrameOffset * mFrameSize.y),
		mFrameSize));
	
}


/**
 * Sets the ultimate destination for a tile and pushes a series of destinations 
 * resulting from a path finding algorithm to get there
 */
void ActorEntity::moveToTile(sf::Vector2i screenPosition)
{
	mSpriteDestination = toSpritePosition(toTilePosition(screenPosition));
}

void ActorEntity::moveToTile(int x, int y)
{
	// Get the ultimate destination based on the Origin of the drawTexture
	mTileDestination = sf::Vector2i(x, y);
	mSpriteDestination = toSpritePosition(mTileDestination);

}

void ActorEntity::setDestination(sf::Vector2i destination)
{
	mElapsedTime = sf::Time::Zero;
	mFrame = 2;

	// Calculate the ultimate destination, centering the feet of the sprite on the tile
	// Find the tile that was clicked
	Pathfinder p(&mWorld->mTilemap);
	while (!mTravelPath.empty()) mTravelPath.pop();
	p.findPath(getTilePosition(), toTilePosition(destination));
	for (auto& i : p.getPath())
	{
		mTravelPath.push(i);	
	}
}


bool ActorEntity::hasReachedDestination()
{
	return mSprite.getPosition() == mSpriteDestination;
}

// Advance the animation by a frame
void ActorEntity::advanceFrame()
{
	if (mFrame == mNumFrames-1)
		mFrame = 1;
	else
		mFrame += 1;

}


void ActorEntity::checkDirection()
{
	if (mDirection & Direction::South)
		mFrameOffset = 0;
	if (mDirection & Direction::North)
		mFrameOffset = 1;
	if (mDirection & Direction::West)
		mFrameOffset = 2;
	if (mDirection & Direction::East)
		mFrameOffset = 3;

}
