#include "Animation.h"


Animation::Animation(void)
{
}

Animation::Animation(sf::Texture& texture)
{
	setTexture(texture);
}


void Animation::initalizeObject()
{
	mFrameSize = sf::Vector2i(0,0);
	mNumFrames = 0;
	mCurrentFrame = 0;
	mDuration = sf::Time::Zero;
	mElapsedTime = sf::Time::Zero;
	mRepeat = false;


}

void Animation::drawCurrent(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(mSprite, states);
}

void Animation::setFrameSize(sf::Vector2i frameSize)
{
	mFrameSize = frameSize;
}

void Animation::setNumFrames(std::size_t frames)
{
	mNumFrames = frames;
}


void Animation::setDuration(sf::Time duration)
{
	mDuration = duration;
}

void Animation::setRepeating(bool repeat)
{
	mRepeat = repeat;
}

sf::Vector2i Animation::getFrameSize()
{
	return mFrameSize;
}


std::size_t Animation::getFrames()
{
	return mNumFrames;
}

sf::Time Animation::getDuration()
{
	return mDuration;
}

bool Animation::getRepeating()
{
	return mRepeat;
}

void Animation::setTexture(sf::Texture& texture)
{
	mSprite.setTexture(texture);
}

void draw(sf::RenderWindow& window, sf::RenderStates states)
{

}
