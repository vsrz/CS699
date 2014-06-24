#include "World.h"
#include "IndicatorEntity.h"


IndicatorEntity::IndicatorEntity(const TextureManager& textures, World* world, ChairEntity* chair)
	: Entity(world)
{
	mDuration = sf::Time(sf::seconds(Config::INDICATOR_ARROW_DURATION));
	mGoingDown = false;
	
	/* no matter what the arrow will be two positions above the chair */
	mStartPosition.x = chair->getTilePosition().x * world->getWorldScale().x;
	mStartPosition.y = (chair->getTilePosition().y - 2) * world->getWorldScale().y;

	mEndPosition.x = mStartPosition.x;
	mEndPosition.y = (chair->getTilePosition().y - 3) * world->getWorldScale().y;


}

// Activate the arrow indicator
void IndicatorEntity::activiate()
{
	mTimer = mDuration;

}

void IndicatorEntity::setDuration(sf::Time seconds)
{
	mDuration = seconds;
}

void IndicatorEntity::updateCurrent(sf::Time dt)
{
	if (mTimer > sf::Time::Zero)
	{
		mTimer -= dt;

		float velocity = 0.f;

		if (mGoingDown && mPosition.y < mStartPosition.y)
		{
			velocity += 1.f;
		}
		else if (!mGoingDown && mPosition.y > mEndPosition.y)
		{
			velocity -= 1.f;
		}
		else
		{
			mGoingDown = !mGoingDown;
		}

	}
	else 
	{
		mGoingDown = false;
		mPosition = mStartPosition;
		mTimer = sf::Time::Zero;
	}
}
