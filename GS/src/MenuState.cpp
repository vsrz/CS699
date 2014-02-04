#include "MenuState.h"
#include "Glob.h"
#include "ResourceHolder.h"

MenuState::MenuState(StateStack& stack, Context context)
	: mBackgroundSprite()
	, State(stack, context)
	, mOptions()
	, mOptionIndex(0)
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	sf::Font& font = context.fonts->get(Fonts::Default);

	// Simple menu
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(exitOption);

	updateOptionText();

}


void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	sf::Texture& texture = getContext().textures->get(Textures::TitleScreen);
	texture.setRepeated(true);
	sf::IntRect rect(0, 0, getContext().window->getSize().x, getContext().window->getSize().y);

	mBackgroundSprite = sf::Sprite(texture, rect);
	
	// Draw the background then all the option elements to the renderwindow
	window.draw(mBackgroundSprite);

	for (const sf::Text& text : mOptions)
	{
		window.draw(text);
	}
}

bool MenuState::update(sf::Time dt)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	// Only handle an event if the keyboard is used
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	if (event.key.code == sf::Keyboard::Return)
	{
		if (mOptionIndex == Play)
		{
			requestStackPop();
			requestStackPush(States::Loading);
		}
		else if (mOptionIndex == Exit)
		{
			// Pop the last element off the stack (itself)
			requestStackPop();
		}
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		// Increment and wrap around
		if (mOptionIndex < mOptions.size() - 1)
		{
			mOptionIndex++;
		}
		else
		{
			mOptionIndex = 0;
		}
		updateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Up)
	{
		// Decrement
		if (mOptionIndex > 0)
		{
			mOptionIndex--;
		}
		else
		{
			mOptionIndex = mOptions.size() - 1;
		}
		updateOptionText();
	}

	return true;
	
}

void MenuState::updateOptionText()
{
	if (mOptions.empty())
	{
		return;
	}

	// Turn the menu white
	for (sf::Text& text : mOptions)
	{
		text.setColor(sf::Color::White);
	}

	// Highlight the selected menu option in red
	mOptions[mOptionIndex].setColor(sf::Color::Red);
}
