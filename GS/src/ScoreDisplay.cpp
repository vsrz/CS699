#include "ScoreDisplay.h"
#include <sstream>


ScoreDisplay::ScoreDisplay(ScoreGenerator* score, sf::Font font)
{
	mScore = score;
	mFont = font;
	initalize();
}

void ScoreDisplay::initalize()
{
	sf::Color color = sf::Color::White;

	mRevenue.setColor(color);
	mRevenue.setPosition(50.f, 740.f);
	mRevenue.setFont(mFont);
	mRevenue.setCharacterSize(14);
	
	
	mTip.setColor(color);
	mTip.setPosition(250.f, 740.f);
	mTip.setFont(mFont);
	mTip.setCharacterSize(14);
	
	mServed.setColor(color);
	mServed.setPosition(500.f, 740.f);
	mServed.setFont(mFont);
	mServed.setCharacterSize(14);
	
	mAngry.setColor(color);
	mAngry.setPosition(900.f, 740.f);
	mAngry.setFont(mFont);
	mAngry.setCharacterSize(14);
		
}

void ScoreDisplay::updateDisplayText()
{
	std::ostringstream ss;
	ss << "Revenue ";
	ss << mScore->getRevenue();
	mRevenue.setString(ss.str());
	mTip.setString("Tips " + mScore->getTips());
	mServed.setString("Customers served " + mScore->getServedCustomers());
	mAngry.setString("Angry customers " + mScore->getUnservedCustomers());
}

void ScoreDisplay::updateCurrent(sf::Time dt)
{
	updateDisplayText();
}

void ScoreDisplay::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mRevenue, states);
	target.draw(mTip, states);
	target.draw(mServed, states);
	target.draw(mAngry, states);
}
