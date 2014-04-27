#include "EndState.h"


EndState::EndState(StateStack& stack, Context context)
	: State(stack, context)
{

}

void EndState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	sf::CircleShape shape(50);
	shape.setFillColor(sf::Color::White);
	window.draw(shape);
}

bool EndState::update(sf::Time dt)
{
	return true;
}

bool EndState::handleEvent(const sf::Event& event)
{
	return false;
}
