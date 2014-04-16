
#include "PetEntity.h"
#include "World.h"
#include "prng.h"

PetEntity::PetEntity(const TextureManager& textures, World* world)
	: ActorEntity(world)
{
	initalize(textures);
}

void PetEntity::initalize(const TextureManager& textures)
{
	mSprite.setTextureRect(sf::IntRect(Config::Pet::SPRITE_ANIM_OFFSET, Config::Pet::SPRITE_ANIM_FRAME_SIZE));
	mSprite.setTexture(textures.get(Textures::Kitty));
	mSprite.setScale(mWorld->getWorldScale());
	mSprite.setOrigin(Config::Pet::SPRITE_ORIGIN_X, Config::Pet::SPRITE_ORIGIN_Y);
	setTilePosition(Config::Pet::SPAWN_POSITION);
	setSpeed(2.f);
	mIrritation = 0;
	mElapsedTime = sf::Time::Zero;
	setDirection(Direction::South);

}

void PetEntity::sleep()
{
	// the cat will sleep in 1 of 2 places, 
	Prng r;
	int roll = r.getRand(0,99);

	if (roll < 50)
	{
		moveToTile(Config::Pet::SLEEP_TILE[0]);
	}

	else
	{
		moveToTile(Config::Pet::SLEEP_TILE[1]);
	}
	mState = State::Sleeping;
	
	// Randomly sleep from 3-8 minutes
	roll = r.getRand(180, 480);
	mElapsedTime += sf::seconds(static_cast<int>(roll));
}

// This is really a scoot function..just move to another close tile
TilePosition PetEntity::findNearestAdjacentTile(TilePosition tile)
{
	float x[16] = {   -1.f,  0.f, 1.f, 0.f,    -1.f, -1.f,  1.f,  1.f,  
		              -2.f, 0.f, 2.f,  0.f,    -2.f, -2.f,  2.f,  2.f};
	float y[16] = {    0.f, -1.f, 0.f, 1.f,    -1.f,  1.f,  1.f, -1.f,  
		               0.f, -2.f, 0.f, 2.f,    -2.f,  2.f,  2.f, -2.f};
	Prng r;
	while(true)
	{
		int i = r.getRand(0,15);
		TilePosition t(tile.x + x[i], tile.y + y[i]); 
		if (mWorld->mTilemap.isValidTile(t))
			return t;
	}
	
	//for (int i = 0; i < 16; ++i)
	//{
	//	TilePosition pos = TilePosition(tile.x + x[i], tile.y + y[i]);
	//	if (!mWorld->mTilemap.isTileOccupied(pos.x, pos.y))
	//	{
	//		return pos;
	//	}
	//}
	
}

/* Move to a random, valid tile */
TilePosition PetEntity::randomTile()
{
	Prng r;
	int x = r.getRand(0,18);
	int y = r.getRand(3,10);
	return TilePosition(static_cast<float>(x),static_cast<float>(y));
}

TilePosition PetEntity::moveNearPlayer()
{
	TilePosition pos = mWorld->getPlayerPosition();
	return pos;
}

void PetEntity::updateState()
{
	Prng r;
	int roll = r.getRand(0,99);

	// Pet will go to her food
	if (roll < 5)
	{
		mState = State::Consumption;
		mElapsedTime += sf::seconds(30.f);
		moveToTile(TilePosition(0,3));
	}

	// Pet will go to a place near the manager
	else if (roll < 20)
	{
		if (mState != State::FollowingManager)
		{
			TilePosition t = findNearestAdjacentTile(moveNearPlayer());
			moveToTile(t);
			mState = State::FollowingManager;
		}
	}

	// Good change that the cat will roam somewhere
	else if (roll < 90)
	{
		moveToTile(randomTile());
		mState = State::Random;
		mElapsedTime += sf::seconds(10.f);
		
		
	}
	
	else if (roll < 99)
	{
		sleep();
	}

	else 
	{
		mState = State::FindingPlayer;
	}
	
	// If the state did not set the time, the next state update will happen
	if (mElapsedTime <= sf::Time::Zero)
	{
		mElapsedTime = sf::seconds(10.f);
	}
}

void PetEntity::checkProximity()
{
	bool move = false;
	if (mState != State::Sleeping && !isMoving())
	{
		if (mWorld->getPlayerPosition() == getTilePosition())
			move = true;
		std::vector<Customer*> customers = mWorld->getCustomers();
		for (int i = 0; i < customers.size(); i++)
		{
			if (move == true) break;
			Customer* cust = customers[i];
			if (cust->getTilePosition() == getTilePosition())
			{
				move = true;
			}
		}
	}

	if (move)
	{
		if (mIrritation < 5)
		{
			moveToTile(findNearestAdjacentTile(getTilePosition()));
			mIrritation += 1;
		} 
		else 
		{
			moveToTile(randomTile());
			setSpeed(3.5f);
			mIrritation = 0;
			
		}
	}
}
void PetEntity::updateCurrent(sf::Time dt)
{

	// Only count the timer down if the cat isn't moving
	if (mElapsedTime <= sf::Time::Zero)
	{
		updateState();
		if (mIrritation > 0)
			mIrritation -= 1;
		setSpeed(2.f);
	} else if (!isMoving()) mElapsedTime -= dt;
	
	if (mState == State::Sleeping)
	{
		if (!isMoving())
		{
			mFrameOffset = 7;
		}
	}

	// Move if anybody jumps into my square
	checkProximity();

	ActorEntity::update(dt);
}




