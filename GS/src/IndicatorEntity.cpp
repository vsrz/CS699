#include "World.h"
#include "IndicatorEntity.h"
#include "ChairEntity.h"

IndicatorEntity::IndicatorEntity(const TextureManager& textures, World* world, ChairEntity* chair)
	: Entity(world)
{
	mDuration = sf::Time(sf::seconds(Config::INDICATOR_ARROW_DURATION));
	mGoingDown = false;
	
	/* no matter what the arrow will be two positions above the chair */
	mStartPosition.x = chair->getTilePosition().x * Config::TILE_WIDTH * world->getWorldScale().x + (Config::TILE_WIDTH / 2.f);
	mStartPosition.y = (chair->getTilePosition().y - 2) * Config::TILE_HEIGHT * world->getWorldScale().y;

	mEndPosition.x = mStartPosition.x;
	mEndPosition.y = (chair->getTilePosition().y - 3) * Config::TILE_HEIGHT * world->getWorldScale().y;

	mSprite.setPosition(mStartPosition);
	mSprite.setTexture(textures.get(Textures::GreenArrow));
	mSprite.setColor(sf::Color(255, 255, 255, 0));

}

// Activate the arrow indicator
void IndicatorEntity::activate()
{
	mTimer = mDuration;
	mSprite.setColor(sf::Color(255, 255, 255, 255));
}

void IndicatorEntity::setDuration(sf::Time seconds)
{
	mDuration = seconds;
}

void IndicatorEntity::setChairType(ChairEntity::Type chairType)
{
	mChairType = chairType;

}

ChairEntity::Type IndicatorEntity::getChairType()
{
	return mChairType;
}

void IndicatorEntity::updateCurrent(sf::Time dt)
{
	if (mTimer > sf::Time::Zero)
	{
		mTimer -= dt;

		float velocity = 0.f;

		if (mGoingDown && mSprite.getPosition().y < mStartPosition.y)
		{
			velocity += Config::INDICATOR_ARROW_SPEED;
		}
		else if (!mGoingDown && mSprite.getPosition().y > mEndPosition.y)
		{
			velocity -= Config::INDICATOR_ARROW_SPEED;
		}
		else
		{
			mGoingDown = !mGoingDown;
		}
		mSprite.setPosition(mSprite.getPosition().x, mSprite.getPosition().y + velocity);

	}
	else 
	{
		mGoingDown = false;
		mSprite.setPosition(mStartPosition);
		mTimer = sf::Time::Zero;
		mSprite.setColor(sf::Color(255, 255, 255, 0));
	}
}
