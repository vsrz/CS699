#ifndef GAMESTATE_H
#define GAMESTATE_H

#pragma once

#include "State.h"
#include "World.h"
#include "ClickObject.h"

class GameState
	: public State
{
public:
	GameState(StateStack& stack, Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

private:
	World mWorld;
	ClickObject mClick;

	bool mDebugOverlay;

};

#endif
