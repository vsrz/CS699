#include "Customer.h"
#include "Glob.h"
#include "World.h"
#include "Pathfinder.h"

Customer::Customer(const TextureManager& textures, World* world, unsigned int customerID)
	: ActorEntity(world)
{
	initalize(textures, customerID);
}

void Customer::initalize(const TextureManager& t, unsigned int customerID)
{
	mSpeed = Config::Customer::RELEASE_INTERVAL;
	mSprite.setTexture(t.get(Textures::TestGuy));
	mSprite.setTextureRect(sf::IntRect(sf::Vector2i(mFrame,mFrameOffset), mFrameSize));
	mSprite.setScale(mWorld->getWorldScale());
	mSprite.setPosition(toSpritePosition(sf::Vector2i(7,3)));

}
void Customer::updateCurrent(sf::Time dt)
{
//	ActorEntity::updateCurrent(dt);
}

void Customer::moveToWaitingArea()
{
//	Pathfinder p(mWorld->mTilemap);
	//p.findPath(
}



