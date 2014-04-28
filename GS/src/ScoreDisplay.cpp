#include "ScoreDisplay.h"
#include <sstream>
#include <iostream>
#include <iomanip>

ScoreDisplay::ScoreDisplay(ScoreGenerator* score, sf::Font font)
{
	mScore = score;
	mFont = font;
	initalize();
}

void ScoreDisplay::initalize()
{
	sf::Color color = sf::Color::White;

	mDisplay.setColor(color);
	mDisplay.setPosition(50.f, 740.f);
	mDisplay.setFont(mFont);
	mDisplay.setCharacterSize(14);
	
}

void ScoreDisplay::updateDisplayText()
{
	std::ostringstream ss;
	ss << std::left << std::setw(8) << "Revenue ";
	ss << std::setw(6) << std::right << mScore->getRevenue();
	ss << std::left << "    ";
	ss << std::setw(5) << "Tips";
	ss << std::setw(6) << std::right << mScore->getTips();
	ss << std::left << "                 ";
	ss << std::setw(18) << "Customers served";
	ss << std::setw(3) << std::right << mScore->getServedCustomers();
	ss << std::left << "    ";
	ss << std::setw(18) << "Angry customers";
	ss << std::setw(3) << std::right << mScore->getUnservedCustomers();
	mDisplay.setString(ss.str());
}

void ScoreDisplay::updateCurrent(sf::Time dt)
{
	updateDisplayText();
}

void ScoreDisplay::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mDisplay, states);
}
