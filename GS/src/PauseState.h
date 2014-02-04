#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#pragma once
#include "State.h"
#include "StateStack.h"
#include <SFML/Graphics.hpp>

class PauseState :
	public State
{
public:
	PauseState(StateStack& stack, Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

private:
	sf::Sprite mBackgroundSprite;
	sf::Text mPauseText;
	sf::Text mInstructionText;

};

#endif
