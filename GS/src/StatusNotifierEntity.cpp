#include "World.h"
#include "StatusNotifierEntity.h"
#include "CustomerState.h"

StatusNotifierEntity::StatusNotifierEntity(const TextureManager& textures, World* world, Customer* customer)
	: Entity(world)

{
	mSprite.setTexture(textures.get(Textures::ID::StatusNotifiers));
	mSprite.setScale(world->getWorldScale());
	mCustomer = customer;
	mWorld = world;
	mOffset = SpritePosition(0, -138.f);
	updateFrame();
}

void StatusNotifierEntity::updateStatus()
{
	unsigned int needs;
	needs = mCustomer->getNeeds();
	
	mFrame = Status::None;

	if (needs & Customer::Needs::Product)
	{
		mFrame = Status::None;
	}

	else if (needs & Customer::Needs::Wash)
	{
		mFrame = Status::Wash;
	}

	else if (needs & Customer::Needs::Cut)
	{
		mFrame = Status::Cut;
	}

	else if (needs & Customer::Needs::Color)
	{
		mFrame = Status::Color;
	}

	// No needs left
	else
	{
		mFrame = Status::Pay;
	}
		

}

// Sets the correct frame on the spritesheet. 
// 0 for cut, 1 for wash, 2 for move, 3 for color, 4 for pay
void StatusNotifierEntity::updateFrame()
{
	sf::Vector2i pos(0,0);
	sf::Vector2i frameSize(Config::TILE_HEIGHT, Config::TILE_WIDTH);

	switch(mFrame)
	{
	case Status::Cut:
		pos.y = 0.f;
		break;
	case Status::Wash:
		pos.y = 32.f;
		break;
	case Status::Walk:
		pos.y = 64.f;
		break;
	case Status::Color:
		pos.y = 96.f;
		break;
	case Status::Pay:
		pos.y = 128.f;
		break;
	default:
		frameSize.x = 0;
		frameSize.y = 0;
		break;
	
	}
	
	sf::IntRect rect(pos, frameSize);
	mSprite.setTextureRect(rect);
}

void StatusNotifierEntity::updatePosition()
{
	mSprite.setPosition(mCustomer->getSpritePosition() + mOffset);
}

void StatusNotifierEntity::updateCurrent(sf::Time dt)
{	
	updateStatus();
	updateFrame();
	updatePosition();
}
