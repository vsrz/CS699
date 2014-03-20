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
sf::Vector2i Entity::getTilePosition()
{
	return toTilePosition(mPosition);
}

void Entity::setTilePosition(sf::Vector2i position)
{
	mPosition = toSpritePosition(position);
}

void Entity::setPosition(sf::Vector2f position)
{
	mPosition = position;
	mBasePosition = position.y + (mWorld->getWorldScale().y * mSprite.getLocalBounds().height) - mSprite.getOrigin().y;
	mSprite.setPosition(position);
}

void Entity::setPosition(sf::Vector2i position)
{
	mSprite.setPosition(toVector2f(position));
}

sf::Vector2i Entity::toTilePosition(sf::Vector2f position)
{
	return toTilePosition(sf::Vector2i(position.x, position.y));
}

sf::Vector2i Entity::toTilePosition(sf::Vector2i position)
{
	return sf::Vector2i(
		static_cast<int>(position.x  / (Config::WORLD_SCALE * Config::TILE_WIDTH)),
		static_cast<int>(position.y  / (Config::WORLD_SCALE * Config::TILE_HEIGHT))
	);

}

sf::Vector2f Entity::toSpritePosition(sf::Vector2i tilePosition)
{
	return sf::Vector2f(
		tilePosition.x * mWorld->getWorldScale().x * Config::TILE_WIDTH,
		tilePosition.y * mWorld->getWorldScale().y * Config::TILE_HEIGHT);
}


void Entity::updateCurrent(sf::Time dt)
{


}

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);

}

