#include "Actor.h"
#include <iostream>

Actor::Actor()
{
}

/** 
 *  Adjusts the velocity of the entity based where they are
 *	and where they are going
 *
 **/
void Actor::findDestination()
{		
	mDirection = 0;
	
	if (mTileDestination.x  > mTilePosition.x)
	{
		mDirection |= Action::Direction::East;
	} 
	else if (mTileDestination.x < mTilePosition.x)
	{
		mDirection |= Action::Direction::West;
	}	

	if (mTileDestination.y  > mTilePosition.y)
	{
		mDirection |= Action::Direction::South;
	} 
	else if (mTileDestination.y < mTilePosition.y)
	{
		mDirection |= Action::Direction::North;
	}
	
	if (mDirection == 0)
	{
		mTileDestination = mTilePosition;
	}
}

/**
 * Returns the current destination for this entity
 **/
sf::Vector2i Actor::getDestination()
{
	return mTileDestination;
}

/* The coordinates that this entity is requested to move to */
void Actor::setDestination(sf::Vector2i destination)
{
	mTileDestination = destination;
}

/* Returns true if there is no current destination set */
bool Actor::hasReachedDestination()
{
	//return mTileDestination == Player::mTilePosition;
}


void Actor::updateCurrent(sf::Time dt)
{
	/**
	 * First check if there's a current destination and adjust the
	 * movement based on the current position on the screen
	 **/
	if (!hasReachedDestination())
	{
		findDestination();
		
		std::cout << std::endl << "Direction: ";
		if (mDirection & Action::Direction::South)
			std::cout << "S";
		if (mDirection & Action::Direction::North)
			std::cout << "N";
		if (mDirection & Action::Direction::West)
			std::cout << "W";
		if (mDirection & Action::Direction::East)
			std::cout << "E";
	}

	/* Offset the position depending on time step--longer time 
		step leads to entity being moved farther over longer time */

}