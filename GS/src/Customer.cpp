#include "Customer.h"
#include "Glob.h"
#include "World.h"
#include "Pathfinder.h"
#include <iostream>

Customer::Customer(const TextureManager& textures, World* world, unsigned int customerID)
	: ActorEntity(world)
{
	initalize(textures, customerID);
}

void Customer::initalize(const TextureManager& t, unsigned int customerID)
{
	ActorEntity::setSpeed(Config::MIDAGE_MAN_SPEED);
	mSprite.setTexture(t.get(Textures::TestGuy));
	mSprite.setTextureRect(sf::IntRect(sf::Vector2i(mFrame,mFrameOffset), mFrameSize));
	mSprite.setScale(mWorld->getWorldScale());
	mSprite.setPosition(toSpritePosition(sf::Vector2i(7,0)));
	mState.setState(CustomerState::ID::None);
	mElapsedTime = sf::Time::Zero;

}
void Customer::updateCurrent(sf::Time dt)
{
	mElapsedTime += dt;
	checkAIState();
	ActorEntity::update(dt);
}

void Customer::moveToWaitingArea()
{
	std::cout << std::endl << "I'm in the salon!";
}

void Customer::enterSalon()
{
	std::stack<sf::Vector2i> travelPath;
	travelPath.push(sf::Vector2i(7,4));
	travelPath.push(sf::Vector2i(7,0));
//	travelPath.push(sf::Vector2i(9,0));
//	travelPath.push(sf::Vector2i(18,0));
	mState.setState(CustomerState::ID::EnteringSalon);
	setTravelPath(travelPath);
}

void Customer::checkAIState()
{
	unsigned int state = mState.getState();

	if (state == CustomerState::ID::None)
	{
		enterSalon();
	}

	else if (state == CustomerState::ID::EnteringSalon)
	{
		if (!isMoving())
		{
			moveToWaitingArea();
			mState.setState(CustomerState::ID::MovingToWaitingArea);
		}
	}
}