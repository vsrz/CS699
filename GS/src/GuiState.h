#ifndef GUISTATE_H
#define GUISTATE_H

#pragma once


#include "State.h"
#include "StateStack.h"
#include <SFGUI/SFGUI.hpp>

class GuiState :
	public State
{
public:
	GuiState(StateStack& stack, Context context);
	void initalize();
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
private:
	sfg::SFGUI mSfgui;
	sfg::Button::Ptr mButton;
	sfg::Desktop mDesktop;
};

#endif
