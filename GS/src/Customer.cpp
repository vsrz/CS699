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
	setTilePosition(TilePosition(7.f,0.f));
	mState.setState(CustomerState::ID::None);
	mElapsedTime = sf::Time::Zero;

}
void Customer::updateCurrent(sf::Time dt)
{
	mElapsedTime += dt;
	checkAIState();
	ActorEntity::update(dt);
}

// Check the current state and handle the click 
void Customer::customerClicked()
{
	unsigned int state = mState.getState();
	ChairEntity* chair;

	if (state == CustomerState::ID::WaitingForService)
	{
		chair = getOccupiedChair();
		if (chair != nullptr)
		{
			std::cout << "Here";

		}

	}
}

ChairEntity* Customer::findAvailableChair(ChairEntity::Type chairType)
{
	std::vector<ChairEntity*> chairs = mWorld->getChairs(chairType);

	for (auto& chair : chairs)
	{
		if (!chair->isOccupied())
		{
			return chair;
		}
	}
	return nullptr;
}

// If the customer is sitting in a chair, return a pointer to it
ChairEntity* Customer::getOccupiedChair()
{
	// Find the waiting room chair that is occupied
	for (auto& chair : mWorld->getChairs(ChairEntity::Type::All))
	{
		// Put them in the chair if they aren't already sitting and update their state
		if (this == chair->getOccupant() && 
			toTilePosition(getPosition()) != chair->getChairLocation())
		{
			return chair;
		}
	}
	return nullptr;

}

void Customer::moveToWaitingArea()
{
	ChairEntity* chair = findAvailableChair(ChairEntity::Type::Waiting);
	if (chair == nullptr)
	{
		std::cout << "No chair available.";
	}
	moveToTile(chair->getTilePosition());
	chair->setOccupied(true, this);


}

void Customer::enterSalon()
{
	Path travelPath;
	travelPath.push(TilePosition(7,0));
	travelPath.push(TilePosition(7,4));
	mState.setState(CustomerState::ID::EnteringSalon);
	moveToTile(travelPath);
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
			ChairEntity* chair = getOccupiedChair();
			if (chair != nullptr)
			{
				Path s;
				s.push(TilePosition(chair->getChairLocation()));					
				moveToTile(s);
				mState.setState(CustomerState::ID::WaitingForService);

			}
		}
	}
	else if (state == CustomerState::ID::WaitingForService)
	{
		// Set the sprite to be waiting in the chair

	}
}