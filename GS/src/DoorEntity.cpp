#include "DoorEntity.h"
#include "Glob.h"
#include "ResourceManager.h"
#include "World.h"
#include "Player.h"
#include "Customer.h"
#include <iostream>

DoorEntity::DoorEntity(const TextureManager& textures, World* world)
	: Entity(world)
{
	mSprite.setTexture(textures.get(Textures::AutoDoors));
	setPosition(toSpritePosition(sf::Vector2i(5,1)));
	mSprite.setScale(world->getWorldScale());
	
	initalize();
}

void DoorEntity::initalize()
{
	mElapsedTime = sf::Time::Zero;
	mAnimDoorOpen.setFrameDuration(sf::milliseconds(80));
	mAnimDoorOpen.setFrameOffset(sf::Vector2i(0,0));
	mAnimDoorOpen.setFrameSize(sf::Vector2i(128,64));
	mAnimDoorOpen.setNumFrames(3);
	mAnimDoorOpen.setRepeating(false);
	mAnimDoorOpen.setStartingFrame(0);
	mAnimDoorOpen.setReverse(false);


	mAnimDoorClose.setFrameDuration(sf::milliseconds(80));
	mAnimDoorClose.setFrameOffset(sf::Vector2i(0,0));
	mAnimDoorClose.setFrameSize(sf::Vector2i(128,64));
	mAnimDoorClose.setNumFrames(3);
	mAnimDoorClose.setRepeating(false);
	mAnimDoorClose.setStartingFrame(3);
	mAnimDoorClose.setReverse(true);
	
	mActiveAnimation = &mAnimDoorOpen;
	
	mSprite.setTextureRect(mActiveAnimation->getFrameWindow());
	setTriggerTiles();
	mState = Closed;
}

void DoorEntity::setTriggerTiles()
{
	triggerTiles.push_back(sf::Vector2i(6,0));
	triggerTiles.push_back(sf::Vector2i(7,0));
	triggerTiles.push_back(sf::Vector2i(6,1));
	triggerTiles.push_back(sf::Vector2i(7,1));
	triggerTiles.push_back(sf::Vector2i(6,2));
	triggerTiles.push_back(sf::Vector2i(7,2));
	triggerTiles.push_back(sf::Vector2i(6,3));
	triggerTiles.push_back(sf::Vector2i(7,3));
}

// See if there's an entity near the door and open or close it
bool DoorEntity::checkDoorToggle()
{
	for (auto& i : triggerTiles)
	{
		if (mWorld->mTilemap.getTileProperty(i.x, i.y) == Tiles::HasActor)
			return true;
	}
}


void DoorEntity::updateCurrent(sf::Time dt)
{
	if (mState == Closed)
	{
		if(checkDoorToggle())
		{
			mState = Opening;
			mActiveAnimation = &mAnimDoorOpen;
			mActiveAnimation->reset();
		}		
	}
	else if (mState == Opening)
	{
		mActiveAnimation->update(dt);
		if(mActiveAnimation->isComplete())
		{
			mState = Open;
		}
	}
	else if (mState == Open)
	{
		if(!checkDoorToggle())
		{
			mState = Closing;
			mActiveAnimation = &mAnimDoorClose;
			mActiveAnimation->reset();
		}
	}
	else if (mState == Closing)
	{
		mActiveAnimation->update(dt);
		if (mActiveAnimation->isComplete())
		{
			mState = Closed;
		}
	}
	mSprite.setTextureRect(mActiveAnimation->getFrameWindow());
}

