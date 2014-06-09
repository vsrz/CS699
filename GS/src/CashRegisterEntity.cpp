#include "World.h"
#include "CashRegisterEntity.h"

CashRegisterEntity::CashRegisterEntity(const TextureManager& textures, World* world, RegisterQueue* queue)
	: Entity(world)
{
	SpritePosition pos = toSpritePosition(Config::RegisterQueue::REGISTER_POSITION[0]);
	mQueue = queue;

	// Setup texture
	sf::IntRect rect(0, 128, static_cast<int>(Config::TILE_HEIGHT), static_cast<int>(Config::TILE_WIDTH));
	mSprite.setTexture(textures.get(Textures::StatusNotifiers));
	mSprite.setScale(world->getWorldScale());
	mSprite.setTextureRect(rect);
	
	mSprite.setPosition(pos.x, pos.y - 16);

	// Image setup
	mFlashDelay = 750;
	mFullBrightness = true;
	mEnabled = false;
}


bool CashRegisterEntity::queueIsActive()
{
	return !mQueue->isEmpty();
}

void CashRegisterEntity::updateCurrent(sf::Time dt)
{
	if (queueIsActive())
	{
		
		if (mEnabled == false)
		{
			mEnabled = true;
			mSprite.setColor(sf::Color(255, 255, 255, 255));
			mTimer = sf::milliseconds(mFlashDelay);
		}
		else
		{
			mTimer -= dt;
			if (mTimer <= sf::Time::Zero)
			{
				mTimer = sf::milliseconds(mFlashDelay);
				if (mFullBrightness)
				{
					mFullBrightness = false;
					mSprite.setColor(sf::Color(128, 128, 128, 255));
				}
				else
				{
					mFullBrightness = true;
					mSprite.setColor(sf::Color(255, 255, 255, 255));
				}
			}
		}
		
	}
	else
	{
		mEnabled = false;
		mSprite.setColor(sf::Color(255, 255, 255, 0));
	}

}