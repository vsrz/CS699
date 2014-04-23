#include "ActionAnimator.h"
#include "Glob.h"
#include "Player.h"

ActionAnimator::ActionAnimator(const TextureManager& textures, World* world, unsigned int animationType, Player* player)
	: Entity(world)
{
	initalize(textures, animationType);
	mPlayer = player;
	mType = animationType;
}

void ActionAnimator::initalize(const TextureManager& t, unsigned int animationType)
{
	/* Default animation frame values */
	sf::Time frameDuration = sf::milliseconds(70);
	sf::Vector2i frameSize(Config::TILE_WIDTH,Config::TILE_HEIGHT);
	sf::Vector2i frameOffset(0,0);
	int frameCount = 0;
	bool animRepeat = false;
	int startingFrame = 0;
	
	// When true, the animation runs in reverse order
	bool reverseAnimation = false;

	// With the animation type, load the appropriate texture, load the anim specific settings
	switch (animationType)
	{
	case Type::Wash:
		mSprite.setTexture(t.get(Textures::AnimWash));
		frameDuration = sf::milliseconds(120);
		frameCount = 30;
		break;

	case Type::Cut:
		mSprite.setTexture(t.get(Textures::AnimCut));
		frameDuration = sf::milliseconds(120);
		frameCount = 30;
		break;

	case Type::Color:
		mSprite.setTexture(t.get(Textures::AnimColor));
		frameDuration = sf::milliseconds(120);
		frameCount = 30;
		break;

	}

	// Load the animation object up
	mAnimation.setFrameDuration(frameDuration);
	mAnimation.setFrameOffset(frameOffset);
	mAnimation.setFrameSize(frameSize);
	mAnimation.setNumFrames(frameCount);
	mAnimation.setRepeating(animRepeat);
	mAnimation.setStartingFrame(startingFrame);
	mAnimation.setReverse(reverseAnimation);

	mLocation = TilePosition(0,0);	
	mState = State::Idle;
	mSprite.setScale(Config::WORLD_SCALE, Config::WORLD_SCALE);
	mAnimation.reset();
	mSprite.setTextureRect(mAnimation.getFrameWindow());


}

// Set the location that this animation will be played when called
void ActionAnimator::setAnimationLocation(TilePosition tilePosition)
{
	mLocation = tilePosition;
	setTilePosition(mLocation);
}

void ActionAnimator::setTriggerTile(TilePosition tilePosition)
{
	mTriggerLocation = tilePosition;
}

void ActionAnimator::updateCurrent(sf::Time dt)
{
	unsigned int playerAction = mPlayer->getCurrentAction();

	if (mType == Type::Wash && playerAction == Player::Action::WashingHair)
	{
		if (mTriggerLocation == mPlayer->getTilePosition())
		{
			mState = State::Playing;
		}
	}
	
	else if (mType == Type::Cut && playerAction == Player::Action::CuttingHair)
	{
		if (mTriggerLocation == mPlayer->getTilePosition())
		{
			mState = State::Playing;
		}
	}

	else if (mType == Type::Color && playerAction == Player::Action::ColoringHair)
	{
		if (mTriggerLocation == mPlayer->getTilePosition())
		{
			mState = State::Playing;
		}
	}

	if (mState == State::Playing)
	{
		mAnimation.update(dt);	
		if (mAnimation.isComplete())
		{
			mAnimation.reset();
			mState = State::Idle;
		}
	}

	if (mPlayer->getCurrentAction() == Player::Action::None)
	{
		mAnimation.reset();
		mState = State::Idle;
	}
	mSprite.setTextureRect(mAnimation.getFrameWindow());


}

