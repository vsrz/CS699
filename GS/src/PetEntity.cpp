
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
	setTilePosition(Config::Pet::SPAWN_POSITION);
	setSpeed(2.f);
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
TilePosition PetEntity::findNearestAdjacentTile(TilePosition tile)
{
	float x[17] = {0, -1.f,  0.f, 1.f, 0.f,    -1.f, -1.f,  1.f,  1.f,  
		              -2.f, 0.f, 2.f,  0.f,    -2.f, -2.f,  2.f,  2.f};
	float y[17] = {0,  0.f, -1.f, 0.f, 1.f,    -1.f,  1.f,  1.f, -1.f,  
		               0.f, -2.f, 0.f, 2.f,    -2.f,  2.f,  2.f, -2.f};
	for (int i = 0; i < 17; ++i)
	{
		TilePosition pos = TilePosition(tile.x + x[i], tile.y + y[i]);
		if (!mWorld->mTilemap.isTileOccupied(pos.x, pos.y))
		{
			return pos;
		}
	}
	
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

	// Pet will not perform any action this tick
	else if (roll < 70)
	{
		mState = State::Idle;
		mElapsedTime += sf::seconds(60.f);
		
		
	}
	
	else if (roll < 90)
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
	
	if (mState != State::Sleeping)
	{
		if (mWorld->getPlayerPosition() == getTilePosition())
		{
			// TODO: Move to a random square
			findNearestAdjacentTile(TilePosition(0,4));
		}
		
	}
}
void PetEntity::updateCurrent(sf::Time dt)
{

	if (mElapsedTime <= sf::Time::Zero)
	{
		updateState();
	} else mElapsedTime -= dt;
	
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




