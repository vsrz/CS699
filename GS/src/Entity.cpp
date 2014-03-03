#include "Entity.h"
#include "World.h"

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
	return toTilePosition(mSprite.getPosition());
}

void Entity::setTilePosition(sf::Vector2i position)
{
	mPosition = toSpritePosition(position);
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

}

sf::Vector2f Entity::toSpritePosition(sf::Vector2i tilePosition)
{
	return sf::Vector2f(
		tilePosition.x * mWorld->getWorldScale().x * 32.f + 0.f,
		tilePosition.y * mWorld->getWorldScale().y * 32.f + 0.f);
}


void Entity::updateCurrent(sf::Time dt)
{


}

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);

}

