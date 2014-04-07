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
	, mType(customerType)
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
	mType = customerType;
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

// Get the state object for the customer
void Customer::leaveStore()
{
	moveToTile(Config::EXIT_TILE);
	mState.setState(CustomerState::ID::Leaving);
}

bool Customer::isReadyToDelete()
{
	return mState.getState() == CustomerState::ID::Delete;
}

void Customer::washHair()
{
	mNeeds &= (Needs::Wash);

	// If they need to go to another station, lets do that
	if (mNeeds & Needs::Cut)
	{
		mState.setState(CustomerState::ID::WaitingToMoveToHaircutArea);
	}
	
	// Otherwise, get up and pay
	else
	{
		mState.setState(CustomerState::ID::MovingToRegister);
	}


}

void Customer::moveToChair(ChairEntity* chair)
{
	// Unoccupy any chair they might already be sitting in
	ChairEntity* currentChair = getOccupiedChair();
	currentChair->setOccupied(nullptr);

	// Occupy the new chair then move to it
	chair->setOccupied(this);
	moveToTile(chair->getStagingPosition());
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
			// If they want a washing service
			if (mNeeds & Needs::Wash)
			{
				// Find an available chair at the washing service
				ChairEntity* washChair = findAvailableChair(ChairEntity::Type::Washing);
				if (washChair != nullptr)
				{
					moveToChair(washChair);
					mState.setState(CustomerState::ID::MovingToWashingArea);

				}
			}
			
			else if (mNeeds & Needs::Cut)
			{
				// Find available chair at the haircut stations
				ChairEntity* cutChair = findAvailableChair(ChairEntity::Type::Cutting);
				if (cutChair != nullptr)
				{
					moveToChair(cutChair);
					mState.setState(CustomerState::ID::MovingToHaircutArea);
				}
			}

		}
	}

	// Customer is waiting for a haircut
	if (state == CustomerState::ID::WaitingForWashService)
	{

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
			toTilePosition(getPosition()) != chair->getChairPosition())
		{
			return chair;
		}
	}
	return nullptr;

}

// Generate a random patience level for this customer
// Patience level is rated 0-10, when customer reaches 0 patience, they walk out
void Customer::setPatience(float bonus)
{
	float patience = (rand() % 10) + 1;
	
	switch(mType)
	{
	case Type::ManOld:
	case Type::ManTeen:
		bonus += .35f;
		break;
	case Type::WomanTeen:
		bonus -= .30f;
		break;
	case Type::ManYoung:
	case Type::WomanYoung:
	case Type::ManMiddle:
	case Type::WomanOld:
	case Type::WomanMiddle:
	default:
		bonus += .25f;
	}
	
	if (patience > 10.f) patience = 10.f;
	mPatience = patience;
}

// Generate this customers needs based on who they are
void Customer::setNeeds()
{
	int roll = getRand(0,99);
	switch (mType)
	{
	case Type::WomanYoung:
	case Type::ManYoung:
	case Type::ManTeen:
		/**
		 *	60% chance for a cut only
		 *  40% chance for wash and cut
		 **/
		if (roll < 60)
		{
			mNeeds = Needs::Cut;
		}

		else
		{
			mNeeds = Needs::Cut | Needs::Wash;
		}
		break;
	case Type::ManMiddle:
		/**
		 *	50% chance for a cut
		 *	30% chance for a wash and cut
		 *  10% chance for product only
		 **/
		if (roll < 50)
		{
			mNeeds = Needs::Cut;
		}

		else if (roll < 70)
		{
			mNeeds = Needs::Cut | Needs::Wash;
		}

		else 
		{
			mNeeds = Needs::Product;
		}
		break;
	case Type::WomanTeen:
	case Type::ManOld:
		/**
		 *	15% chance for a cut
		 *  25% chance for a wash and cut
		 *	40% chance for a wash, cut, and color
		 *  20% chance for product only
		 **/
		if (roll < 15)
		{
			mNeeds = Needs::Cut;
		}

		else if (roll < 40)
		{
			mNeeds = Needs::Cut | Needs::Wash;
		}

		else if (roll < 80)
		{
			mNeeds = Needs::Cut | Needs::Wash | Needs::Color;
		}

		else 
		{
			mNeeds = Needs::Product;
		}
		break;
	case Type::WomanMiddle:
		/**
		 *  30% chance for a wash and cut
		 *	50% chance for a wash, cut, and color
		 *  20% chance for product only
		 **/
		if (roll < 30)
		{
			mNeeds = Needs::Cut | Needs::Wash;
		}

		else if (roll < 80)
		{
			mNeeds = Needs::Cut | Needs::Wash | Needs::Color;
		}

		else {
			mNeeds = Needs::Product;
		}
		break;
	
	case Type::WomanOld:
		break;
	default:
		/**
		 * 15% chance of wanting only product
		 * 40% chance of wanting a wash and cut
		 * 10% chance of wanting a wash, cut, and color
		 * 30% chance of wanting only a cut
		 * 5% chance of wanting only a wash
		 */
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

		else
		{
			mNeeds = Needs::Wash;
		}
	}
	// Register testing
	// mNeeds = Needs::Product;

	// TODO: Remove this
	// Wash to Register test
	mNeeds = Needs::Wash;
	assert(mNeeds > 0);
	
}

// Set their speed based on the customer type
void Customer::setSpeed()
{
	float speed = 3.f;
	switch(mType)
	{
	case Type::ManYoung:
		speed = 5.f;
		break;
	case Type::ManTeen:
	case Type::ManMiddle:
		speed = 4.5f;
		break;
	case Type::WomanTeen:
	case Type::WomanMiddle:
	case Type::WomanYoung:
		speed = 3.f;
		break;
	case Type::ManOld:
	case Type::WomanOld:
	default:
		speed = 2.f;
	}
	ActorEntity::setSpeed(speed);
	
}


void Customer::moveToWaitingArea()
{
	ChairEntity* chair = findAvailableChair(ChairEntity::Type::Waiting);
	if (chair == nullptr)
	{
		std::cout << "No chair available.";
	}
	moveToTile(chair->getStagingPosition());
	chair->setOccupied(this);
}


void Customer::enterSalon()
{
	Path travelPath;
	travelPath.push(TilePosition(7,0));
	travelPath.push(TilePosition(7,4));
	mState.setState(CustomerState::ID::EnteringSalon);
	moveToTile(travelPath);
#ifdef DEBUG
	std::cout << std::endl << "Needs: ";
	if (mNeeds & Needs::Wash) std::cout << "Wash ";
	if (mNeeds & Needs::Cut) std::cout << "Cut ";
	if (mNeeds & Needs::Dry) std::cout << "Dry ";
	if (mNeeds & Needs::Color) std::cout << "Color ";
	if (mNeeds & Needs::Product) std::cout << "Product ";
#endif
}


void Customer::checkAIState()
{
	unsigned int state = mState.getState();
	ChairEntity* occupiedChair = getOccupiedChair();

	if (state == CustomerState::ID::None)
	{
		enterSalon();
	}

	else if (state == CustomerState::ID::EnteringSalon)
	{
		if (!isMoving())
		{
			moveToWaitingArea();
			if (mNeeds != Needs::Product)
			{
				mState.setState(CustomerState::ID::MovingToWaitingArea);
			} 
			else
			{
				mWorld->getQueue()->enqueue(this);
				mState.setState(CustomerState::ID::MovingToRegister);
			}

		}
	}

	else if (state == CustomerState::ID::MovingToWaitingArea)
	{
		if (!isMoving())
		{
			if (occupiedChair != nullptr)
			{
				// TODO: Replace this with a sitting texture
				TilePosition t = occupiedChair->getChairPosition();
				Entity::setTilePosition(t);
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

	else if (state == CustomerState::ID::MovingToWashingArea)
	{
		if (!isMoving())
		{
			TilePosition t = occupiedChair->getChairPosition();
			Entity::setTilePosition(t);
			mState.setState(CustomerState::ID::WaitingForWashService);
		}
	}
	else if (state == CustomerState::ID::MovingToHaircutArea)
	{
		if (!isMoving())
		{
			TilePosition t = occupiedChair->getChairPosition();
			Entity::setTilePosition(t);
			mState.setState(CustomerState::ID::WaitingForHaircutService);
		}
	}
	else if (state == CustomerState::ID::MovingToRegister)
	{
		if (!isMoving())
		{			
			int queuePos = mWorld->getQueue()->getQueuePosition(this);
			if (queuePos < 0) queuePos = 0;
			setDirection(Config::RegisterQueue::DIRECTION[queuePos]);
			mState.setState(CustomerState::ID::WaitingToPay);

		}
	}
	
	else if (state == CustomerState::ID::Leaving)
	{
		if (!isMoving())
		{
			mState.setState(CustomerState::ID::Delete);
		}
	}

	// Customer has exited the store and is no longer needed in the scenegraph
	else if (state == CustomerState::ID::Delete)
	{
		
	}

}