#ifndef TITLESTATE_H
#define TITLESTATE_H

#pragma once

#include "State.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class TitleState
	: public State
{
public:
	TitleState(StateStack& stack, Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

private:
	sf::Sprite mBackgroundSprite0;
	sf::Sprite mBackgroundSprite1;
	sf::Sprite mBackgroundSprite2;

	sf::Text mText;

	bool mShowText;
	sf::Time mTextEffectTime;
};

#endif
