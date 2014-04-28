#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include <SFML/Graphics.hpp>
#include "SceneNode.h"
#include "ScoreGenerator.h"

#pragma once
class ScoreDisplay
	: public SceneNode
{
public:
	ScoreDisplay(ScoreGenerator* score, sf::Font font);
	virtual ~ScoreDisplay(void) {}

	

private:
	sf::Text mRevenue;
	sf::Text mTip;
	sf::Text mServed;
	sf::Text mAngry;
	sf::Font mFont;

	void initalize();

	ScoreGenerator* mScore;
	void updateDisplayText();

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time dt);
};

#endif
