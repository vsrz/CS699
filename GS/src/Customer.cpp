#include "Customer.h"
#include "Glob.h"
#include "World.h"

Customer::Customer(const TextureManager& textures, World* world)
	: ActorEntity(world)
{
	mSpeed = Config::Customer::RELEASE_INTERVAL;
}


Customer::~Customer(void)
{
}

void Customer::updateCurrent(sf::Time dt)
{
	updateCurrent(dt);
}




