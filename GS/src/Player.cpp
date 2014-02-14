#include "ResourceManager.h"
#include "Player.h"
#include <iostream>

Player::Player(const TextureManager& textures, World* worldContext) 
	: mSprite(textures.get(Textures::TestGuy))
	, mWorld(worldContext)
	, mSpeed(0.8f)
	, mFrameSize(32.f, 64.f)
{
	mSprite.setTextureRect(sf::IntRect(sf::Vector2i(0,0), mFrameSize));
	mSprite.setOrigin(0.f,64.f);
	mSprite.setPosition(mWorld->getPixelsFromTilePosition(
		sf::Vector2i(1,1)));
	mTilePosition = mWorld->getTilePosition(sf::Vector2i(
		static_cast<int>(mSprite.getPosition().x),
		static_cast<int>(mSprite.getPosition().y)));
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);

}

void Player::setDestination(sf::Vector2i destination)
{
	mTileDestination = destination;
}

bool Player::hasReachedDestination()
{
	return mTileDestination == mTilePosition;
}

void Player::updateCurrent(sf::Time dt)
{
	movementUpdate += dt;
	if (!hasReachedDestination())
	{
		sf::Vector2f currentPosition = mSprite.getPosition();
		sf::Vector2f destPosition = mWorld->getPixelsFromTilePosition(mTileDestination);
		sf::Vector2f movement;
		/*
		if (destPosition.x > currentPosition.x)
			movement.x = 1.f;
		else if (destPosition.x < currentPosition.x)
			movement.x = -1.f;

		if (destPosition.y > currentPosition.y)
			movement.y = 1.f;
		else if (destPosition.y < currentPosition.y)
			movement.y = -1.f;
			
		currentPosition += movement;
		*/mSprite.setPosition(destPosition);
		movementUpdate -= sf::seconds(1.f);

	}

	mTilePosition = mWorld->getTilePosition(sf::Vector2i(
		static_cast<int>(mSprite.getPosition().x),
		static_cast<int>(mSprite.getPosition().y)));
}

unsigned int Player::getCategory() const 
{ 
	return Category::Player; 
}


