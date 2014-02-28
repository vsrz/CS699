#include "ResourceManager.h"
#include "Player.h"
#include "Glob.h"
#include <iostream>
#include <map>
#include <string>

#define TILE_HEIGHT 32
#define TILE_WIDTH
 
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
	, mSpawnPosition(7,3)
	, mTravelPath()
{
	mSprite.setTextureRect(sf::IntRect(sf::Vector2i(mFrame,mFrameOffset), mFrameSize));
	mSprite.setOrigin(0.f,32.f);
	mSprite.setScale(mScale);
	mTilePosition = mSpawnPosition;
	mTileDestination = mTilePosition;
	mSprite.setPosition(toSpritePosition(mTilePosition));
	mSpriteDestination = mSprite.getPosition();
	mBoundingBox = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
}

sf::Vector2i Player::toTilePosition(sf::Vector2f position)
{
	return toTilePosition(sf::Vector2i(position.x, position.y));
}

sf::Vector2i Player::toTilePosition(sf::Vector2i position)
{
	return sf::Vector2i(
		static_cast<int>(position.x  / (32.f * mWorld->getWorldScale().x)),
		static_cast<int>(position.y  / (32.f * mWorld->getWorldScale().y)));

}

sf::Vector2f Player::toSpritePosition(sf::Vector2i tilePosition)
{
	return sf::Vector2f(
		tilePosition.x * mWorld->getWorldScale().x * 32.f + 0.f,
		tilePosition.y * mWorld->getWorldScale().y * 32.f + 0.f);
}

// Return the current position that the player is standing in
sf::Vector2i Player::getCurrentTilePosition()
{
	return toTilePosition(mSprite.getPosition());
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape shape(sf::Vector2f(mBoundingBox.width * 2, mBoundingBox.height));
	shape.setFillColor(sf::Color(255,0,0,128));
	shape.setPosition(mSprite.getPosition());
	//target.draw(shape, states);
	target.draw(mSprite, states);
}

/**
 * Sets the ultimate destination for a tile and pushes a series of destinations 
 * resulting from a path finding algorithm to get there
 */
void Player::moveToTile(int x, int y)
{
	// Get the ultimate destination based on the Origin of the drawTexture
	mTileDestination = sf::Vector2i(x, y);
	mSpriteDestination = toSpritePosition(mTileDestination);


}

void Player::setDestination(sf::Vector2i destination)
{
	mElapsedTime = sf::Time::Zero;
	mFrame = 2;

	// Calculate the ultimate destination, centering the feet of the sprite on the tile
	// Find the tile that was clicked
	Pathfinder p(&mWorld->mTilemap);
	while (!mTravelPath.empty()) mTravelPath.pop();
	p.findPath(mTilePosition, toTilePosition(destination));
	for (auto& i : p.getPath())
	{
		mTravelPath.push(i);	
	}

}

bool Player::hasReachedDestination()
{
	return mSprite.getPosition() == mSpriteDestination;
}

void Player::updateCurrent(sf::Time dt)
{
#ifdef DEBUG
	extern std::map<std::string, std::string> g_debugData;
	g_debugData["TilePos"] = toString(toTilePosition(mTilePosition).x) + toString(toTilePosition(mTilePosition).y);

#endif
	mElapsedTime += dt;

	if (!mTravelPath.empty())
	{
		mTileDestination = mTravelPath.top();
		mSpriteDestination = toSpritePosition(mTileDestination);
		sf::Vector2f currentPosition = mSprite.getPosition();
		sf::Vector2f destPosition = toSpritePosition(mTileDestination);
		sf::Vector2f movement;
		
		// If the sprite is within 5 pixels of its destination just snap it
		if (abs(destPosition.x - currentPosition.x) < 5.f)
			currentPosition.x = destPosition.x;
	
		if (abs(destPosition.y - currentPosition.y) < 5.f)
			currentPosition.y = destPosition.y;
	
		// Set the movement direction 
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

		// Update the position of the sprite on the screen
		currentPosition += movement * mSpeed;
		mSprite.setPosition(currentPosition);

		// update movement animation and direction if necessary
		if (mElapsedTime > sf::seconds(0.12f))
		{
			checkDirection();
			mElapsedTime -= sf::seconds(0.12f);
			advanceFrame();

		}
		// If this move causes the destination to be reached, remove it from the queue.
		if (hasReachedDestination())
		{
			mTravelPath.pop();
			if (mTravelPath.empty())
			{
				mFrame = 0;
			}
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
	mTilePosition = toTilePosition(mSprite.getPosition());
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


