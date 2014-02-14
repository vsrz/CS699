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



void Entity::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
 	mVelocity.x += vx;
	mVelocity.y += vy;
}



void Entity::updateCurrent(sf::Time dt)
{

	/* Offset the position depending on time step--longer time 
		step leads to entity being moved farther over longer time */
	move(mVelocity * dt.asSeconds());


}

