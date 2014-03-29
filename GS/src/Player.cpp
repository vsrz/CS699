#include "ResourceManager.h"
#include "Player.h"
#include "Glob.h"
#include <iostream>
#include <map>
#include <string>
#include "World.h"

Player::Player(const TextureManager& textures, World* worldContext) 
	: ActorEntity(worldContext)
	, mWorld(worldContext)
{
	initalize(textures);
}
Player::Player(const TextureManager& textures, World* worldContext, unsigned int playerID) 
	: ActorEntity(worldContext)
	, mWorld(worldContext)
{
	initalize(textures);
	ActorEntity::setSpeed(Config::MANAGER_SPEED);

}

void Player::initalize(const TextureManager& t)
{
	mSprite.setTexture(t.get(Textures::TestGuy));
	mSprite.setTextureRect(sf::IntRect(sf::Vector2i(mFrame,mFrameOffset), mFrameSize));
	mSprite.setOrigin(0.f,32.f);
	mSprite.setScale(mWorld->getWorldScale());
	mTilePosition = TilePosition(11,4);
	mTileDestination = mTilePosition;
	mSprite.setPosition(toSpritePosition(mTilePosition));
	mBoundingBox = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
	mElapsedTime = sf::Time::Zero;

}


void Player::updateCurrent(sf::Time dt)
{
#ifdef DEBUG
	extern std::map<std::string, std::string> g_debugData;
	g_debugData["TilePos"] = toString(toTilePosition(mTilePosition).x) + toString(toTilePosition(mTilePosition).y);
	g_debugData["Actor YPos"] = toString(getPosition().y);
#endif
	mElapsedTime += dt;
	ActorEntity::update(dt);

}

unsigned int Player::getCategory() const 
{ 
	return Category::Player; 
}


