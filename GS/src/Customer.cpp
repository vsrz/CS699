#include "Customer.h"
#include "Glob.h"
#include "World.h"
#include "Pathfinder.h"
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
	mType = customerType;
	
	// Roll is used for selecting between different customer textures
	int roll = rng.getRand(0,99);
	
	switch(customerType)
	{
	case Type::WomanTeen:
		mSprite.setTexture(t.get(Textures::WomanTeen01));
		break;
	case Type::ManTeen:
		mSprite.setTexture(t.get(Textures::ManTeen01));
		break;
	case Type::WomanMiddle:
		mSprite.setTexture(t.get(Textures::WomanMidage01));
		break;
	case Type::WomanOld:
		mSprite.setTexture(t.get(Textures::WomanOld01));
		break;
	case Type::ManYoung:
		mSprite.setTexture(t.get(Textures::ManYoung01));
		break;
	default:
		mSprite.setTexture(t.get(Textures::WomanTeen01));
	}
	
	mSprite.setTextureRect(sf::IntRect(Config::Customer::SPRITE_ANIM_OFFSET, Config::Customer::SPRITE_ANIM_FRAME_SIZE));
	mSprite.setScale(mWorld->getWorldScale());
	mSprite.setOrigin(Config::Customer::BASE_SPRITE_ORIGIN_X,Config::Customer::BASE_SPRITE_ORIGIN_Y);
	setTilePosition(Config::Customer::SPAWN_POSITION);
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

float Customer::getPatience()
{
	return mPatience;		
}

/*	Returns the highest pixel on the customer image. Useful for making sure the icons
	don't float too high or too low above the head of the customer */
float Customer::getHeight()
{
	return mHeight;
}

void Customer::updateCurrent(sf::Time dt)
{
	Prng n;
	mElapsedTime += dt;
	checkAIState();
	ActorEntity::update(dt);

	// Controls how often the patience for a customer is reduced
	if (mElapsedTime.asSeconds() > 10 + 
		mWorld->getCustomers().size() + 
		n.getRand(0, 10))
	{
		updatePatience();
		mElapsedTime = sf::Time::Zero;
	}

	
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

// Returns true if the customer is waiting to move to another station
bool Customer::isWaitingToMoveToStation()
{
	unsigned int state = mState.getState();
	return (
		state == CustomerState::ID::WaitingForService ||
		state == CustomerState::ID::WaitingToMoveToColorArea ||
		state == CustomerState::ID::WaitingToMoveToHaircutArea
		);
}

void Customer::washHair()
{
	mNeeds &= ~(Needs::Wash);
	ChairEntity* occupiedChair = getOccupiedChair();
	// If they need to go to another station, lets do that
	if (mNeeds & Needs::Cut)
	{
		mState.setState(CustomerState::ID::WaitingToMoveToHaircutArea);

	}
	
	// Otherwise, get up and pay
	else
	{
		stand(occupiedChair);
		cashOut();		
	}


}

void Customer::cutHair()
{
	mNeeds &= ~(Needs::Cut);
	ChairEntity* occupiedChair = getOccupiedChair();
	// If they need to go to another station, lets do that
	if (mNeeds & Needs::Color)
	{
		ChairEntity* haircutChair = findAvailableChair(ChairEntity::Type::Coloring);
		if (haircutChair != nullptr)
		{
			mState.setState(CustomerState::ID::WaitingToMoveToColorArea);
		}
	}
	
	// Otherwise, get up and pay
	else
	{
		stand(occupiedChair);
		cashOut();		
	}

}

void Customer::colorHair()
{
	mNeeds &= ~(Needs::Color);
	ChairEntity* occupiedChair = getOccupiedChair();
	stand(occupiedChair);
	cashOut();		
}

void Customer::moveToChair(ChairEntity* chair)
{
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
					
					mState.setState(CustomerState::ID::MovingToWashingArea);
					stand(chair);
					moveToChair(washChair);

				}
			}
			
			else if (mNeeds & Needs::Cut)
			{
				// Find available chair at the haircut stations
				ChairEntity* cutChair = findAvailableChair(ChairEntity::Type::Cutting);
				if (cutChair != nullptr)
				{
					
					mState.setState(CustomerState::ID::MovingToHaircutArea);
					stand(chair);
					moveToChair(cutChair);
				}
			}

		}
	}	

	// Customer is waiting to move to the haircut area, so if they are clicked, find a seat and move them
	else if (state == CustomerState::ID::WaitingToMoveToHaircutArea)
	{
		ChairEntity* haircutChair = findAvailableChair(ChairEntity::Type::Cutting);
		ChairEntity* occupiedChair = getOccupiedChair();
		if (haircutChair != nullptr)
		{
			mState.setState(CustomerState::ID::MovingToHaircutArea);
			stand(occupiedChair);
			moveToChair(haircutChair);
		}
	}

	else if (state == CustomerState::ID::WaitingToMoveToColorArea)
	{
		ChairEntity* colorChair = findAvailableChair(ChairEntity::Type::Coloring);
		ChairEntity* occupiedChair = getOccupiedChair();
		if (colorChair != nullptr)
		{
			mState.setState(CustomerState::ID::MovingToColorArea);
			stand(occupiedChair);
			moveToChair(colorChair);
		}
	}
}

unsigned int Customer::getState()
{
	return mState.getState();

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
	float patience = (rand() % 50) + 50;
	
	switch(mType)
	{
	case Type::ManOld:
	case Type::ManTeen:
		bonus += 35.f;
		break;
	case Type::WomanTeen:
		bonus -= 30.f;
		break;
	case Type::ManYoung:
	case Type::WomanYoung:
	case Type::ManMiddle:
	case Type::WomanOld:
	case Type::WomanMiddle:
	default:
		bonus += 25.f;
	}
	
	if (patience < 30.f) patience = 30.f;
	mPatience = patience;
}

// Generate this customers needs based on who they are
void Customer::setNeeds()
{
	int roll = rng.getRand(0,99);
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
	// TODO: Remove this test code
	//mNeeds = Needs::Wash;

	// TODO: Remove this
	// Wash to Register test
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

void Customer::cashOut()
{
	mWorld->getQueue()->enqueue(this);
	mState.setState(CustomerState::ID::MovingToRegister);
}

/* Decreases or increases patience based on current action */
void Customer::updatePatience()
{

	// Don't penalize if they haven't entered the scene yet
	if (mState.getState() == CustomerState::ID::Arrived || 
		mState.getState() == CustomerState::ID::EnteringSalon || 
		mState.getState() == CustomerState::ID::Leaving || 
		mState.getState() == CustomerState::ID::Delete)
	{
		return;
	}

	// Otherwise, penalize them
	Prng n;
	mPatience -= 5 + n.getRand(0,4) + 1;

	if (mPatience < 0) mPatience = 0;
	

	// Leave the salon if we've got no patience left
	if (mPatience <= 0 && 
		(mState.getState() != CustomerState::ID::Leaving || 
		mState.getState() != CustomerState::ID::Delete ||
		mState.getState() != CustomerState::ID::WaitingToPay ||
		mState.getState() != CustomerState::ID::MovingToRegister))
	{
		ChairEntity* chair = getOccupiedChair();
		mNeeds = 0;
		if (chair != nullptr)
			stand(getOccupiedChair());
		leaveStore();
	}
	
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
			if (mNeeds != Needs::Product)
			{
				moveToWaitingArea();
				mState.setState(CustomerState::ID::MovingToWaitingArea);
			} 
			else
			{
				cashOut();
			}

		}
	}

	else if (state == CustomerState::ID::MovingToWaitingArea)
	{
		if (!isMoving())
		{
			if (occupiedChair != nullptr)
			{
				if (!isSitting())
					sit(occupiedChair);
				else
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
			if (!isSitting())
			{
				sit(occupiedChair);
				mState.setState(CustomerState::ID::WaitingForWashService);
			}
		}
	}

	else if (state == CustomerState::ID::WaitingForWashService)
	{
		if (!isMoving())
		{				
			
		}
	}

	else if (state == CustomerState::ID::MovingToHaircutArea)
	{
		if (!isMoving())
		{
			TilePosition t = occupiedChair->getChairPosition();
			sit(occupiedChair);
			mState.setState(CustomerState::ID::WaitingForHaircutService);
		}
	}

	else if (state == CustomerState::ID::MovingToColorArea)
	{
		if (!isMoving())
		{
			TilePosition t = occupiedChair->getChairPosition();
			sit(occupiedChair);
			mState.setState(CustomerState::ID::WaitingForColorService);
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
		if (getTilePosition() == Config::EXIT_TILE && !isMoving())
		{
			mState.setState(CustomerState::ID::Delete);
		}
	}

	// Customer has exited the store and is no longer needed in the scenegraph
	else if (state == CustomerState::ID::Delete)
	{
		
	}

}

