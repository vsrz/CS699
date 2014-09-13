#ifndef ENDSTATE_H
#define ENDSTATE_H

#pragma once
#include "state.h"
#include "ScoreGenerator.h"
#include <string>
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
	void saveScore(std::string scoreString);

	sf::RectangleShape mBackground;
	sf::Text mThankYou;
	sf::Text mPressToRestart;
	sf::Text mScoreString;
};

#endif
