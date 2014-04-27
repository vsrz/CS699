#include "EndState.h"
#include <iostream>

EndState::EndState(StateStack& stack, Context context)
	: State(stack, context)
{
	temp = false;
}

void EndState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	sf::CircleShape shape(50);
	shape.setFillColor(sf::Color::White);
	window.draw(shape);
}

void EndState::setScore(ScoreGenerator score)
{
	mScore = score;
}

bool EndState::update(sf::Time dt)
{
	if (temp == false)
	{
		std::cout << mScore.getScoreString() << "\n";
		temp = true;
	}

	return true;
}

bool EndState::handleEvent(const sf::Event& event)
{
	return false;
}
