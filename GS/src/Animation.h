#ifndef ANIMATION_H
#define ANIMATION_H

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Animation
{
public:
	Animation(void);
	explicit Animation(const sf::Texture& texture);
	void initalizeObject(void);

	void setFrameOffset(sf::Vector2i frameOffset);
	void setFrameSize(sf::Vector2i frameSize);
	void setNumFrames(std::size_t frames);
	void setDuration(sf::Time duration);
	void setRepeating(bool repeat);
	void setTexture(const sf::Texture& texture);

	sf::Sprite& getSprite();

	sf::Vector2i getFrameSize();
	std::size_t getFrames();
	sf::Time getDuration();
	bool getRepeating();

	void update(sf::Time dt);

private:
	sf::Vector2i mFrameOffset;
	sf::Vector2i mFrameSize;
	std::size_t mNumFrames;
	std::size_t mCurrentFrame;
	sf::Time mDuration;
	sf::Time mElapsedTime;
	bool mRepeat;

	sf::Sprite mSprite;



};

#endif
