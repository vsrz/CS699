#include "ActorEntity.h"
#include "Pathfinder.h"
#include "World.h"
#include "Glob.h"
#include <iostream>

ActorEntity::ActorEntity(World* world)
	: mTravelPath()
	, Entity(world)
	, mFrameSize(32.f, 64.f)
	, mFrameOffset(3)
	, mFrame(0)
	, mNumFrames(6)
	, mSpeed(5.f)

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

// Calculates the amount of movement for the sprite
sf::Vector2f ActorEntity::moveSprite(sf::Vector2f pos, sf::Vector2f dest)
{
	sf::Vector2f movement;
	float speed = mSpeed;
		
	// Set the movement direction 
	if (dest.x > pos.x)
	{
		movement.x = 1.f;
		mDirection = Direction::East;
	}
	else if (dest.x < pos.x)
	{
		movement.x = -1.f;
		mDirection = Direction::West;
	}
	if (dest.y > pos.y)
	{
		movement.y = 1.f;
		mDirection = Direction::South;
	}
	else if (dest.y < pos.y)
	{
		movement.y = -1.f;
		mDirection = Direction::North;
	}

	// Adjust diagnoal movement speed
	if (movement.x != 0 && movement.y != 0)
	{
		speed *= 0.71f;
	}
	pos += movement * speed;

	// Snaps the player to a square. This is used when the correct pixel
	// position for a tile is rounded and caused by floating point divison 
	if (abs(dest.x - pos.x) < 2.f)
		pos.x = dest.x;
	
	if (abs(dest.y - pos.y) < 2.f)
		pos.y = dest.y;

	mSprite.setPosition(pos);
	return pos;
}

void ActorEntity::update(sf::Time dt)
{
	// Check for movement
	if (!mTravelPath.empty())
	{
		mTileDestination = mTravelPath.top();
		mSpriteDestination = toSpritePosition(mTileDestination);
		sf::Vector2f destPosition = toSpritePosition(mTileDestination);
		sf::Vector2f currentPosition;

		// Move the sprite and update the position
		currentPosition = moveSprite(mSprite.getPosition(), destPosition);
		checkDirection();

		// update movement animation and direction if necessary
		if (mElapsedTime > sf::seconds(0.12f))
		{
			mElapsedTime -= sf::seconds(0.12f);
			advanceFrame();
		}

		// If this move causes the destination to be reached, remove it from the stack.
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
	setDestination(screenPosition);
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
