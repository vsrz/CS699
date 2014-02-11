#include "ActorEntity.h"


ActorEntity::ActorEntity()
{
}

/** 
 *  Adjusts the velocity of the entity based where they are
 *	and where they are going
 *
 **/
void ActorEntity::findDestination()
{	
	unsigned int direction = 0;
	
	if (mTileDestination.x  > mTilePosition.x)
	{
		direction += Direction::East;
	} 
	else if (mTileDestination.x < mTilePosition.x)
	{
		direction += Direction::West;
	}	

	if (mTileDestination.y  > mTilePosition.y)
	{
		direction += Direction::South;
	} 
	else if (mTileDestination.y < mTilePosition.y)
	{
		direction += Direction::North;
	}
}


/* The coordinates that this entity is requested to move to */
void ActorEntity::setDestination(sf::Vector2i destination)
{
	mTileDestination = destination;
}

/* Returns true if there is no current destination set */
bool ActorEntity::hasReachedDestination()
{
	return !mTileDestination.x && !mTileDestination.y;
}


void ActorEntity::updateCurrent(sf::Time dt)
{
	/**
	 * First check if there's a current destination and adjust the
	 * movement based on the current position on the screen
	 **/
	if (!hasReachedDestination())
	{
		findDestination();
	}

	/* Offset the position depending on time step--longer time 
		step leads to entity being moved farther over longer time */

}