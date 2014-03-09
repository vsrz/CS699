#ifndef ANIMATION_H
#define ANIMATION_H

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Animation
{
public:
	Animation(void);
	void initalizeObject(void);

	void setFrameOffset(sf::Vector2i frameOffset);
	void setFrameSize(sf::Vector2i frameSize);
	void setNumFrames(int frames);
	void setFrameDuration(sf::Time duration);
	void setRepeating(bool repeat);
	void setStartingFrame(int startingFrame);
	void setReverse(bool reverse);
	void reset();


	sf::IntRect getFrameWindow();
	sf::Vector2i getFrameSize();
	int getFrames();
	sf::Time getDuration();
	bool getRepeating();
	bool isComplete();

	sf::IntRect update(sf::Time dt);

private:
	sf::Vector2i mFrameOffset;
	sf::Vector2i mFrameSize;
	int mNumFrames;
	int mCurrentFrame;
	int mStartingFrame;

	sf::Time mFrameDuration;
	sf::Time mElapsedTime;
	bool mRepeat;
	bool mReverse;
	int mComplete;


};

#endif
