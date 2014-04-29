#ifndef LOADINGSTATE_H
#define LOADINGSTATE_H

#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateStack.h"
#include "ParallelTask.h"

class LoadingState
	: public State
{
public:
	LoadingState(StateStack& stack, Context context);
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
	virtual bool setCompletion(float percent);
	virtual void draw();

private:
	sf::Text mLoadingText;
	sf::RectangleShape mProgressBar;
	float mMaxProgressSize;
	sf::RectangleShape mProgressBarBackground;
	ParallelTask mLoadingTask;
};

#endif

