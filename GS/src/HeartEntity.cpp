#include "World.h"
#include "HeartEntity.h"


HeartEntity::HeartEntity(const TextureManager& textures, World* world, float love, Customer* customer)
	: Entity(world)
{ 
	mSprite.setTexture(textures.get(Textures::ID::Hearts));
	mSprite.setScale(mWorld->getWorldScale());	
	mCustomer = customer;
}

void HeartEntity::setMaxFill(float fill)
{
	mLoveMax = fill;
}


void HeartEntity::setFill(float fill)
{
	mLove = fill;
}

// Updates the frame number based on the percentage of love left
void HeartEntity::updateFrame()
{
	float percent = mLove / mLoveMax;
	int frame = 0;

	if (percent <= 85)
		frame++;
	if (percent <= 70)
		frame++;
	if (percent <= 55)
		frame++;
	if (percent <= 40)
		frame++;
	if (percent <= 25)
		frame++;
	if (percent <= 10)
		frame++;
	if (percent <= 3)
		frame = 7;

	setFrame(frame);

}

// Sets the correct frame on the heart spritesheet
void HeartEntity::setFrame(int frame)
{
	mFrame = frame;
	sf::Vector2i pos(0,0);
	sf::Vector2i frameSize(Config::TILE_HEIGHT * Config::WORLD_SCALE, Config::TILE_WIDTH * Config::WORLD_SCALE);

	if (mFrame == 0 || mFrame % 2 > 0)
		pos.x = 0;
	else
		pos.x = Config::TILE_WIDTH;

	pos.y = (mFrame / 2) * Config::TILE_HEIGHT;
	
	sf::IntRect rect(pos, frameSize);
	mSprite.setTextureRect(rect);
}

void HeartEntity::updateStatusPosition()
{
	mSprite.setPosition(mCustomer->getPosition());
}

void HeartEntity::updateCurrent(sf::Time dt)
{

	Entity::update(dt);
}

