#include "Animation.h"
#include <iostream>

Animation::Animation(void)
{
}

Animation::Animation(const sf::Texture& texture)
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

// Set the position where the animation begins. Default is 0,0 (top left corner)
void Animation::setFrameOffset(sf::Vector2i frameOffset)
{
	mFrameOffset = frameOffset;
}

// The size of each animation frame in the texture
void Animation::setFrameSize(sf::Vector2i frameSize)
{
	mFrameSize = frameSize;
}

// Number of frames to render for this animation
void Animation::setNumFrames(std::size_t frames)
{
	mNumFrames = frames;
}

// The length of time to display a frame
void Animation::setDuration(sf::Time duration)
{
	mDuration = duration;
}

// When true, the animation will be repeated as long as update is called
void Animation::setRepeating(bool repeat)
{
	mRepeat = repeat;
}

// The base texture used 
void Animation::setTexture(const sf::Texture& texture)
{
	mSprite.setTexture(texture);
}

// Returns the size of each frame
sf::Vector2i Animation::getFrameSize()
{
	return mFrameSize;
}

// Returns the number of frames in this animation
std::size_t Animation::getFrames()
{
	return mNumFrames;
}

// Returns the duration of each frame
sf::Time Animation::getDuration()
{
	return mDuration;
}

bool Animation::getRepeating()
{
	return mRepeat;
}

// Returns a reference to the sprite
sf::Sprite& Animation::getSprite()
{
	return mSprite;
}

void Animation::update(sf::Time dt)
{

}