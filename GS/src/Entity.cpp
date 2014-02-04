#include "Entity.h"

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;

}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}



/* Private Members */

/** 
 *  Adjusts the velocity of the entity based where they are
 *	and where they are going
 *
 **/
void Entity::findDestination()
{
	
}

void Entity::updateCurrent(sf::Time dt)
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
	move(mVelocity * dt.asSeconds());


}

void Entity::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
 	mVelocity.x += vx;
	mVelocity.y += vy;
}


/* The coordinates that this entity is requested to move to */
void Entity::setDestination(sf::Vector2i destination)
{
	mDestination = destination;
}

/* Returns true if there is no current destination set */
bool Entity::hasReachedDestination()
{
	return !mDestination.x && !mDestination.y;
}
