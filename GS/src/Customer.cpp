#include "Customer.h"
#include "Glob.h"
#include "World.h"
#include "Pathfinder.h"
#include "prng.h"
#include <iostream>
#include <cstdlib>
#include <cassert>

Customer::Customer(const TextureManager& textures, World* world, unsigned int customerType)
	: ActorEntity(world)
{
	initalize(textures, customerType);
}

void Customer::initalize(const TextureManager& t, unsigned int customerType)
{
	mSprite.setTexture(t.get(Textures::TestGuy));
	mSprite.setTextureRect(sf::IntRect(sf::Vector2i(mFrame,mFrameOffset), mFrameSize));
	mSprite.setScale(mWorld->getWorldScale());
	mSprite.setOrigin(0.f,32.f);
	setTilePosition(TilePosition(7.f,0.f));
	mState.setState(CustomerState::ID::None);
	
	setSpeed();
	setNeeds();
	setPatience();
	
	mElapsedTime = sf::Time::Zero;

}

unsigned int Customer::getNeeds()
{
	return mNeeds;
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

	// Customer is waiting for service
	if (state == CustomerState::ID::WaitingForService)
	{
		chair = getOccupiedChair();
		if (chair != nullptr)
		{
			

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

// Generate a random patience level for this customer
// Patience level is rated 0-10, when customer reaches 0 patience, they walk out
// TODO: Create some dependence on the customer type
void Customer::setPatience(float bonus)
{
	float patience = (rand() % 10) + 1;
	patience *= 1.25f;
	patience += bonus;
	if (patience > 10.f) patience = 10.f;
	mPatience = patience;
}

// TODO: Create some form of classification for different customer types (IDs)
void Customer::setNeeds()
{
	/**
	 * 15% chance of wanting only product
	 * 40% chance of wanting a wash and cut
	 * 10% chance of wanting a wash, cut, and color
	 * 30% chance of wanting only a cut
	 * 5% chance of wanting only a wash
	 */
	int roll = getRand(0,99);
	if (roll < 15)
	{
		mNeeds = Needs::Product;
	}

	else if (roll < 55)
	{
		mNeeds = Needs::Wash | Needs::Cut;
	}

	else if (roll < 65)
	{
		mNeeds = Needs::Wash | Needs::Cut | Needs::Color;
	}

	else if (roll < 95)
	{
		mNeeds = Needs::Cut;
	}

	else if (roll < 100)
	{
		mNeeds = Needs::Wash;
	}
	assert(mNeeds > 0);
	
}

// TODO: Come up with some form of depth here to calculate speed
void Customer::setSpeed()
{
	float speed = 3.f;
	ActorEntity::setSpeed(speed);
	
}


void Customer::moveToWaitingArea()
{
	ChairEntity* chair = findAvailableChair(ChairEntity::Type::Waiting);
	if (chair == nullptr)
	{
		std::cout << "No chair available.";
	}
	moveToTile(chair->getTilePosition());
	chair->setOccupied(this);


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
		if (!isMoving())
		{

		}

	}
}