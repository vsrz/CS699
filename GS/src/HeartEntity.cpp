#include "World.h"
#include "HeartEntity.h"


HeartEntity::HeartEntity(const TextureManager& textures, World* world, Customer* customer)
	: Entity(world)
{ 
	mSprite.setTexture(textures.get(Textures::ID::Hearts));
	mSprite.setScale(mWorld->getWorldScale());	
	mCustomer = customer;
	mLoveMax = 100.f;
	updateStatusPosition();
	updateFrame();
	mOffset = SpritePosition(0, -116.f);
}

void HeartEntity::setMaxFill(float fill)
{
	mLoveMax = fill;
}


void HeartEntity::setFill(float fill)
{
	mLove = fill;
}

void HeartEntity::setCustomerHeightOffset(SpritePosition offset)
{
	mOffset = offset;
}

// Updates the frame number based on the percentage of love left
void HeartEntity::updateFrame()
{
	float percent = mLove / mLoveMax * 100;
	int frame = 0;

	if (percent <= 88)
		frame++;
	if (percent <= 76)
		frame++;
	if (percent <= 64)
		frame++;
	if (percent <= 52)
		frame++;
	if (percent <= 40)
		frame++;
	if (percent <= 28)
		frame++;
	if (percent <= 16)
		frame = 7;
	setFrame(frame);

}

// Sets the correct frame on the heart spritesheet
void HeartEntity::setFrame(int frame)
{
	mFrame = frame;
	sf::Vector2i pos(0,0);
	sf::Vector2i frameSize(static_cast<int>(Config::TILE_HEIGHT), static_cast<int>(Config::TILE_WIDTH));

	if (mFrame == 0 || mFrame % 2 == 0)
		pos.x = 0;
	else
		pos.x = static_cast<int>(Config::TILE_WIDTH);

	pos.y = (mFrame / 2) * static_cast<int>(Config::TILE_HEIGHT);
	
	sf::IntRect rect(pos, frameSize);
	mSprite.setTextureRect(rect);
}

void HeartEntity::updateStatusPosition()
{
	mSprite.setPosition(mCustomer->getSpritePosition() + mOffset);
}

void HeartEntity::updateCurrent(sf::Time dt)
{
	mLove = mCustomer->getPatience();
	updateStatusPosition();
	updateFrame();
}

