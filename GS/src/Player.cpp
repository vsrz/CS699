#include "ResourceManager.h"
#include "Player.h"
#include "Glob.h"
#include <iostream>
#include <map>
#include <string>
#include "World.h"
#include "RegisterQueue.h"
#include "ChairEntity.h"
#include "Customer.h"


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
	mCurrentAction = None;

}


unsigned int Player::getState()
{
	return mState;
}

void Player::setState(unsigned int state)
{
	mState = state;
}

void Player::useRegister(RegisterQueue* queue)
{
	mCurrentAction = Action::UsingRegister;
	mRegisterQueue = queue;
	setState(State::Busy);

}

void Player::useStation(ChairEntity* chair)
{
	unsigned int chairType = chair->getChairType();

	switch (chairType)
	{
	case ChairEntity::Washing:
		if (chair->getOccupant()->getState() == CustomerState::ID::WaitingForWashService)
			mCurrentAction = Action::WashingHair;
		break;
	case ChairEntity::Cutting:
		if (chair->getOccupant()->getState() == CustomerState::ID::WaitingForHaircutService)
			mCurrentAction = Action::CuttingHair;
		break;
	case ChairEntity::Coloring:
		if (chair->getOccupant()->getState() == CustomerState::ID::WaitingForColorService)
			mCurrentAction = Action::ColoringHair;
		break;
	default:
		mCurrentAction = Action::None;
	}
	
	// Store the customer we're working on so we can manipulate them
	if (mCurrentAction > Action::None)
	{
		mCurrentCustomer = chair->getOccupant();
	}

}

// Set the player to be busy for the amount of seconds
// While the player is busy, they cannot perform any actions except
// ordering customers to move to the next station
void Player::setBusy(sf::Time seconds)
{
	mBusyTime = seconds;
	setState(State::Busy);
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
	
	if (mBusyTime > sf::Time::Zero)
	{
		mBusyTime -= dt;
	}
	else
	{
		// If they are currently using the register
		if (mCurrentAction == Action::UsingRegister)
		{
			// Ring someone up
			mRegisterQueue->dequeue();

			// If there is nobody else in line, change the action and remove their busy toggle
			if (mRegisterQueue->isEmpty())
			{
				mCurrentAction = Action::None;
				mRegisterQueue = nullptr;
				setState(State::Idle);
			}

			// Otherwise, take another customer, after the USE_TIME elapses
			else
			{
				mBusyTime += sf::seconds(Config::REGISTER_USE_TIME);
			}
		}
		else if (mCurrentAction == Action::WashingHair)
		{
			if (getState() != State::Busy)
			{
				mBusyTime += sf::seconds(Config::WASH_USE_TIME);
				setState(State::Busy);
			}
			else
			{
				mCurrentAction = Action::None;
				mCurrentCustomer->washHair();
				setState(State::Idle);
			}
		}
		else if (mCurrentAction == Action::CuttingHair)
		{
			if (getState() != State::Busy)
			{
				mBusyTime += sf::seconds(Config::CUT_USE_TIME);
				setState(State::Busy);
			}
			else
			{
				mCurrentAction = Action::None;
				mCurrentCustomer->cutHair();
				setState(State::Idle);
			}
		}
		else if (mCurrentAction == Action::ColoringHair)
		{
			if (getState() != State::Busy)
			{
				mBusyTime += sf::seconds(Config::COLOR_USE_TIME);
				setState(State::Busy);
			}
			else
			{
				mCurrentAction = Action::None;
				mCurrentCustomer->colorHair();
				setState(State::Idle);
			}
		}

	}

}

unsigned int Player::getCategory() const 
{ 
	return Category::Player; 
}


