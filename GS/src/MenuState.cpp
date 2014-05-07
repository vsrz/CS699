#include "MenuState.h"
#include "Glob.h"
#include "ResourceManager.h"

MenuState::MenuState(StateStack& stack, Context context)
	: mBackgroundSprite0()
	, mBackgroundSprite1()
	, mBackgroundSprite2()
	, State(stack, context)
	, mOptions()
	, mOptionIndex(0)
{
	sf::Texture& texture0 = getContext().textures->get(Textures::TitleScreen0);
	sf::Texture& texture1 = getContext().textures->get(Textures::TitleScreen1);
	sf::Texture& texture2 = getContext().textures->get(Textures::TitleScreen2);

	sf::Font& font = context.fonts->get(Fonts::Default);

	// Simple menu
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	playOption.setCharacterSize(36);
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setCharacterSize(36);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 40.f));
	mOptions.push_back(exitOption);

	updateOptionText();

}


void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	sf::Texture& texture0 = getContext().textures->get(Textures::TitleScreen0);
	sf::Texture& texture1 = getContext().textures->get(Textures::TitleScreen1);
	sf::Texture& texture2 = getContext().textures->get(Textures::TitleScreen2);
	
	sf::IntRect rect0(0, 0, 426, getContext().window->getSize().y);
	sf::IntRect rect1(426, 0, 426, getContext().window->getSize().y);
	sf::IntRect rect2(852, 0, 428, getContext().window->getSize().y);

	mBackgroundSprite0 = sf::Sprite(texture0, rect0);
	mBackgroundSprite1 = sf::Sprite(texture1, rect1);
	mBackgroundSprite2 = sf::Sprite(texture2, rect2);

	window.draw(mBackgroundSprite0);
	window.draw(mBackgroundSprite1);
	window.draw(mBackgroundSprite2);

	mBackgroundSprite0 = sf::Sprite(texture0);
	mBackgroundSprite0.setPosition(sf::Vector2f(0.f, 0.f));
	mBackgroundSprite1 = sf::Sprite(texture1);
	mBackgroundSprite1.setPosition(sf::Vector2f(426.f, 0.f));
	mBackgroundSprite2 = sf::Sprite(texture2);
	mBackgroundSprite2.setPosition(sf::Vector2f(852.f, 0.f));

	// Draw the background then all the option elements to the renderwindow
	window.draw(mBackgroundSprite0);
	window.draw(mBackgroundSprite1);
	window.draw(mBackgroundSprite2);

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
