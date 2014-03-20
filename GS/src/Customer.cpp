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
	mSprite.setOrigin(0.f,32.f);
	setPosition(toSpritePosition(sf::Vector2i(7,0)));
	mState.setState(CustomerState::ID::None);
	mElapsedTime = sf::Time::Zero;

}
void Customer::updateCurrent(sf::Time dt)
{
	mElapsedTime += dt;
	checkAIState();
	ActorEntity::update(dt);
}

ChairEntity* Customer::findAvailableChair()
{
	WaitingChairsPtr chairs = mWorld->getWaitingRoomChairs();

	for (auto& chair : *chairs)
	{
		if (!chair->isOccupied())
		{
			return chair.get();
		}
	}
	return nullptr;
}

void Customer::moveToWaitingArea()
{
	ChairEntity* chair = findAvailableChair();
	if (chair == nullptr)
	{
		std::cout << "No chair available.";
	}
	setDestination(toVector2i(toSpritePosition(chair->getTilePosition())));
	chair->setOccupied(true, this);


}

void Customer::enterSalon()
{
	std::stack<sf::Vector2i> travelPath;
	travelPath.push(sf::Vector2i(7,4));
	travelPath.push(sf::Vector2i(7,0));
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

	else if (state == CustomerState::ID::MovingToWaitingArea)
	{
		if (!isMoving())
		{
			// Find the waiting room chair that is occupied
			ChairEntity* chair;
			for (auto& chair : *mWorld->getWaitingRoomChairs())
			{
				// Put them in the chair if they aren't already sitting and update their state
				if (this == chair->getOccupant() && 
					toVector2i(mPosition) != chair->getChairLocation())
				{
					std::stack<sf::Vector2i> s;
					s.push(sf::Vector2i(chair->getChairLocation()));
					setTravelPath(s);
					mState.setState(CustomerState::ID::WaitingForService);

				}
			}
		}
	}
}