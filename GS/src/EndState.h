#pragma once
#include "state.h"
class EndState :
	public State
{
public:
	EndState(StateStack& stack, Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
};

