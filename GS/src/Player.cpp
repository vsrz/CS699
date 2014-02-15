#include "ResourceManager.h"
#include "Player.h"
#include "Glob.h"
#include <iostream>

Player::Player(const TextureManager& textures, World* worldContext) 
	: mSprite(textures.get(Textures::TestGuy))
	, mWorld(worldContext)
	, mSpeed(5.f)
	, mFrameSize(32.f, 64.f)
	, mScale(mWorld->getWorldScale())
	, mFrameOffset(3)
	, mFrame(0)
	, mNumFrames(6)
	, mElapsedTime(sf::Time::Zero)
{
	mSprite.setTextureRect(sf::IntRect(sf::Vector2i(0,0), mFrameSize));
	mSprite.setOrigin(0.f,32.f);
	mSprite.setScale(mScale);
	mTilePosition = mWorld->getTilePosition(sf::Vector2i(
		static_cast<int>(mSprite.getPosition().x),
		static_cast<int>(mSprite.getPosition().y)));
	mSprite.setPosition(toVector2f(mTilePosition));
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(mSprite, states);

}


void Player::setDestination(sf::Vector2i destination)
{
	mElapsedTime = sf::Time::Zero;
	mFrame = 2;
	mTileDestination.x = destination.x - mFrameSize.x * mScale.x * 0.5f;
	mTileDestination.y = destination.y - mFrameSize.y * mScale.y * 0.2f;
}

bool Player::hasReachedDestination()
{
	return mTileDestination == mTilePosition;
}

void Player::updateCurrent(sf::Time dt)
{
	mElapsedTime += dt;

	if (!hasReachedDestination())
	{
		sf::Vector2f currentPosition = mSprite.getPosition();
		sf::Vector2f destPosition = toVector2f(mTileDestination);
		sf::Vector2f movement;
		
		if (abs(destPosition.x - currentPosition.x) < 5.f)
			currentPosition.x = destPosition.x;
	
		if (abs(destPosition.y - currentPosition.y) < 5.f)
			currentPosition.y = destPosition.y;
	
		if (destPosition.x > currentPosition.x)
		{
			movement.x = 1.f;
			mDirection = Direction::East;
		}
		else if (destPosition.x < currentPosition.x)
		{
			movement.x = -1.f;
			mDirection = Direction::West;
		}
		if (destPosition.y > currentPosition.y)
		{
			movement.y = 1.f;
			mDirection = Direction::South;
		}
		else if (destPosition.y < currentPosition.y)
		{
			movement.y = -1.f;
			mDirection = Direction::North;
		}

		// TODO: If the move you're about to make puts you in a blocking tile,
		// do not make the move and set the destination vector to the curent position
		

		currentPosition += movement * mSpeed;
		mSprite.setPosition(currentPosition);

		// Check the direction every frame
		checkDirection();

		// update movement animation
		if (mElapsedTime > sf::seconds(0.12f))
		{
			mElapsedTime -= sf::seconds(0.12f);
			advanceFrame();

		}
	}
	else
	{
		// Movement complete, rest sprite
		mFrame = 0;
	}
	mSprite.setTextureRect(
		sf::IntRect(sf::Vector2i(mFrame * mFrameSize.x, mFrameOffset * mFrameSize.y),
		mFrameSize));
	mTilePosition = toVector2i(mSprite.getPosition());
}

void Player::checkDirection()
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

// Advance the animation by a frame
void Player::advanceFrame()
{
	if (mFrame == mNumFrames-1)
		mFrame = 1;
	else
		mFrame += 1;

}

unsigned int Player::getCategory() const 
{ 
	return Category::Player; 
}


