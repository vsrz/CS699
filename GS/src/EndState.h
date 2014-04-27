#ifndef ENDSTATE_H
#define ENDSTATE_H

#pragma once
#include "state.h"
#include "ScoreGenerator.h"
class EndState :
	public State
{
public:
	EndState(StateStack& stack, Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	void setScore(ScoreGenerator score);
private:
	ScoreGenerator mScore;
	bool temp;
};

#endif
