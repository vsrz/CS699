#include "Entity.h"

Entity::Entity(World* world, float speed)
	: mWorld(world)
	, mSpeed(speed)
{}

Entity::~Entity() {}

void Entity::setSpeed(float speed)
{
	mSpeed = speed;
}

float Entity::getSpeed()
{
	return mSpeed;
}

void Entity::setSprite(sf::Sprite &sprite)
{
	mSprite = sprite;
}

sf::Vector2i Entity::toTilePosition(sf::Vector2f position)
{
	return toTilePosition(sf::Vector2i(position.x, position.y));
}

sf::Vector2i Entity::toTilePosition(sf::Vector2i position)
{
	return sf::Vector2i(
		static_cast<int>(position.x  / (32.f * mWorld->getWorldScale().x)),
		static_cast<int>(position.y  / (32.f * mWorld->getWorldScale().y)));
	mWorld

}

sf::Vector2f Entity::toSpritePosition(sf::Vector2i tilePosition)
{
	return sf::Vector2f(
		tilePosition.x * mWorld->getWorldScale().x * 32.f + 0.f,
		tilePosition.y * mWorld->getWorldScale().y * 32.f + 0.f);
}


// Return the current position that the entity is currently occupying
sf::Vector2i Entity::getCurrentTilePosition()
{
	return toTilePosition(mSprite.getPosition());
}


void Entity::update(sf::Time dt)
{


}

void Entity::draw()
{

}

