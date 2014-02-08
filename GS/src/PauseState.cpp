
#include "PauseState.h"
#include "ResourceManager.h"
#include "Glob.h"

PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
	, mBackgroundSprite()
	, mPauseText()
	, mInstructionText()
{
	sf::Font& font = context.fonts->get(Fonts::Default);
	sf::Vector2f viewSize = context.window->getView().getSize();

	mPauseText.setFont(font);
	mPauseText.setString("Paused");
	mPauseText.setCharacterSize(70);
	centerOrigin(mPauseText);
	mPauseText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	mInstructionText.setFont(font);
	mInstructionText.setString("Press Backspace to return to the main menu");
	centerOrigin(mInstructionText);
	mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0,0,0,150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPauseText);
	window.draw(mInstructionText);
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	if (event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
	}
	else if (event.key.code == sf::Keyboard::BackSpace)
	{
		requestStateClear();
		requestStackPush(States::Menu);
	}
	else if (event.key.code == sf::Keyboard::Q)
	{
		requestStateClear();
	}

	return false;
}