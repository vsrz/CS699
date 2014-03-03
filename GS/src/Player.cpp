#include "ResourceManager.h"
#include "Player.h"
#include "Glob.h"
#include <iostream>
#include <map>
#include <string>
#include "World.h"

#define TILE_HEIGHT 32
#define TILE_WIDTH 32
 
Player::Player(const TextureManager& textures, World* worldContext) 
	: ActorEntity(worldContext)
	, mWorld(worldContext)
	, mSpeed(Config::GMANAGER_SPEED)
	, mScale(mWorld->getWorldScale())
	, mElapsedTime(sf::Time::Zero)
{
	mSprite.setTexture(textures.get(Textures::TestGuy));
	mSprite.setTextureRect(sf::IntRect(sf::Vector2i(mFrame,mFrameOffset), mFrameSize));
	mSprite.setOrigin(0.f,32.f);
	mSprite.setScale(mScale);
	mTilePosition = sf::Vector2i(7,3);
	mTileDestination = mTilePosition;
	mSprite.setPosition(toSpritePosition(mTilePosition));
	mBoundingBox = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
}

void Player::updateCurrent(sf::Time dt)
{
#ifdef DEBUG
	extern std::map<std::string, std::string> g_debugData;
	g_debugData["TilePos"] = toString(toTilePosition(mTilePosition).x) + toString(toTilePosition(mTilePosition).y);

#endif
	mElapsedTime += dt;
	ActorEntity::update(dt);

}

unsigned int Player::getCategory() const 
{ 
	return Category::Player; 
}


