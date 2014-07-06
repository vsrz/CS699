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

private:
	sfg::SFGUI mSfgui;
};

#endif
