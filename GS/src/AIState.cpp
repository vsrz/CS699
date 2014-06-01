#include "AIState.h"
#include "World.h"
#include <iostream>
#include <vector>

AIState::~AIState()
{

}

AIState::AIState()
{
	//mPlayer = nullptr;
	mLastUpdate = sf::Time::Zero;
}


void AIState::setPlayer(Player* player)
{
	mPlayer = player;
	
}

void AIState::setWorld(World* world)
{
	mWorld = world;
}

void AIState::initalize()
{
	mGameState.ColorLowestPatience = nullptr;
	mGameState.CutLowestPatience = nullptr;
	mGameState.WashLowestPatience = nullptr;
	mGameState.WaitingLowestPatience = nullptr;
	mGameState.OpenColorChairs = 0;
	mGameState.OpenColorChairs = 0;
	mGameState.OpenCutChairs = 0;
	mGameState.OpenWaitingChairs = 0;
	mGameState.OpenWashChairs = 0;
	mGameState.RegQueueLowestHeart = 0.f;
}

void AIState::update(sf::Time dt)
{
	mLastUpdate += dt;

	if (mLastUpdate >= sf::seconds(2.f))
	{
		mLastUpdate = sf::Time::Zero;
		mGameState.WaitingLowestPatience = getLowestHeart(SalonService::Waiting);
		if (mGameState.WaitingLowestPatience != nullptr)
		{
			std::cout << "The lowest patience is " << mGameState.WaitingLowestPatience->getPatience() << ".\n";
			mGameState.WaitingLowestPatience->customerClicked();
		}
	}

}

Customer* AIState::getLowestHeart(SalonService service)
{
	std::vector<ChairEntity*> chairs;
	float heart = -1.f;
	Customer* customer = nullptr;
	switch (service)
	{
	case SalonService::Waiting:
		chairs = mWorld->getChairs(ChairEntity::Type::Waiting);
		break;
	case SalonService::Wash:
		chairs = mWorld->getChairs(ChairEntity::Type::Washing);
		break;
	case SalonService::Cut:
		chairs = mWorld->getChairs(ChairEntity::Type::Cutting);
		break;
	case SalonService::Color:
		chairs = mWorld->getChairs(ChairEntity::Type::Coloring);
		break;
	case SalonService::Register:
		// Special case?
		return customer;
		break;
	default:
		// This should never happen
		throw std::exception("Invalid SalonService supplied in getLowestHeart()");
	}

	for (auto &c : chairs)
	{
		// If this chair is occupied, test the hearts and assign it back
		// The customer must be seated to be considered
		if (c->isOccupied())
		{
			// If the lowest heart hasnt been set, set it
			if (heart == -1)
			{
				if (c->getOccupant()->isSitting())
				{
					heart = c->getOccupant()->getPatience();
					customer = c->getOccupant();
				}
				
			}
			else
			{
				// Otherwise, compare it to this customer
				if (c->getOccupant()->getPatience() < heart && c->getOccupant()->isSitting())
				{
					customer = c->getOccupant();
					heart = customer->getPatience();
				}
			}
			
		}
	}

	return customer;

}

