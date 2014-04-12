
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

TilePosition PetEntity::findNearestAdjacentTile(TilePosition tile)
{
	float x[16] = {-1.f, 0.f, 1.f, 0.f, 0.f, -1.f, 0.f, -1.f,-2.f, 0.f, 2.f, 0.f, 0.f, -2.f, 0.f, -2.f};
	float y[16] = {0.f, -1.f, 0.f, 1.f, -1.f, 0.f, 1.f, 0.f,-2.f, 0.f, 2.f, 0.f, 0.f, -2.f, 0.f, -2.f};
	for (int i = 0; i < 16; ++i)
	{
		TilePosition pos = TilePosition(tile.x + x[i], tile.y + y[i]);
		if (!mWorld->mTilemap.isTileOccupied(pos))
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

	if (roll < 5)
	{
		mState = State::Consumption;
	}
	else if (roll < 20)
	{
		if (mState != State::FollowingManager)
		{
			moveToTile(moveNearPlayer());
			mState = State::FollowingManager;
		}
	}
	else if (roll < 70)
	{
		mState = State::Idle;
		
		
	}
	
	else if (roll < 90)
	{
		mState = State::Sleeping;
		moveToTile(TilePosition(0,3));
	}

	else 
	{
		mState == State::FindingPlayer;
	}


}
void PetEntity::updateCurrent(sf::Time dt)
{

	if (mElapsedTime <= sf::Time::Zero)
	{
		updateState();
		mElapsedTime = sf::seconds(10.f);
		std::cout << mState << std::endl;
	} else mElapsedTime -= dt;

	ActorEntity::update(dt);
}




