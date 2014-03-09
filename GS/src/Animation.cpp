#include "Animation.h"
#include <iostream>

Animation::Animation(void)
{
}

void Animation::initalizeObject()
{
	mFrameSize = sf::Vector2i(0,0);
	mNumFrames = 0;
	mCurrentFrame = 0;
	mFrameDuration = sf::Time::Zero;
	mElapsedTime = sf::Time::Zero;
	mRepeat = false;
	mComplete = -1;
	mReverse = false;

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
void Animation::setNumFrames(int frames)
{
	mNumFrames = frames;
}

// The length of time to display a frame
void Animation::setFrameDuration(sf::Time duration)
{
	mFrameDuration = duration;
}

// When true, the animation will be repeated as long as update is called
void Animation::setRepeating(bool repeat)
{
	mRepeat = repeat;
}

void Animation::setReverse(bool reverse)
{
	mReverse = reverse;
}

void Animation::setStartingFrame(int frame)
{
	mStartingFrame = frame;
	mCurrentFrame = frame;
}


sf::IntRect Animation::getFrameWindow()
{
	return sf::IntRect(
		sf::Vector2i(
			mFrameOffset.x,
			mFrameOffset.y + (mFrameSize.y * mCurrentFrame)),
		sf::Vector2i(
			mFrameSize.x,
			mFrameSize.y)
		);
}

void Animation::reset()
{
	mCurrentFrame = mStartingFrame;
	mComplete = -1;
}

// Returns the size of each frame
sf::Vector2i Animation::getFrameSize()
{
	return mFrameSize;
}

// Returns the number of frames in this animation
int Animation::getFrames()
{
	return mNumFrames;
}

// Returns the duration of each frame
sf::Time Animation::getDuration()
{
	return mFrameDuration;
}

bool Animation::getRepeating()
{
	return mRepeat;
}

bool Animation::isComplete()
{
	return mComplete == 1;
}


// Update the frame and return the new position in the animation
sf::IntRect Animation::update(sf::Time dt)
{
	mElapsedTime += dt;
	if (mElapsedTime >= mFrameDuration)
	{
		mElapsedTime -= mFrameDuration;

		if (mReverse)
		{
			// Loop the animation, or stop if repeating is disabled
			if (mCurrentFrame + mStartingFrame - 1 < 0 + mStartingFrame)
			{
				if (mRepeat)
					mCurrentFrame = mStartingFrame;
				mComplete = 1;
			}
			else
			{
				mCurrentFrame--;			
				mComplete = 0;
			}
		}
		else
		{
			// Loop the animation, or stop if repeating is disabled
			if (mCurrentFrame - mStartingFrame + 1 > mNumFrames)
			{
				if (mRepeat)
					mCurrentFrame = mStartingFrame;
				mComplete = 1;
			}
			else
			{
				mCurrentFrame++;			
				mComplete = 0;
			}
		}
	}
	return getFrameWindow();
}
