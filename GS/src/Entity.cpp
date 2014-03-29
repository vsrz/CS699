#include "Entity.h"
#include "World.h"
#include "Glob.h"

Entity::Entity(World* world)
	: mWorld(world)
{}

Entity::~Entity() {}

void Entity::setSprite(sf::Sprite &sprite)
{
	mSprite = sprite;
}

void Entity::setTextureRect(sf::IntRect rect)
{
	mSprite.setTextureRect(rect);
}

sf::IntRect Entity::getTextureRect()
{
	return mSprite.getTextureRect();
}

// Return the current position that the entity is currently occupying
TilePosition Entity::getTilePosition()
{
	return toTilePosition(mSprite.getPosition());
}

void Entity::setTilePosition(TilePosition position)
{
	SpritePosition pos = toSpritePosition(position);
	mSprite.setPosition(pos);
}

void Entity::setPosition(SpritePosition position)
{
	mSprite.setPosition(position);
}

void Entity::updateCurrent(sf::Time dt)
{
}

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);

}

float Entity::getZPosition()
{
	return mSprite.getPosition().y;
}

