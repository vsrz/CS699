#include "MenuState.h"
#include "Glob.h"
#include "ResourceManager.h"

MenuState::MenuState(StateStack& stack, Context context)
	: mBackgroundSprite0()
	, mBackgroundSprite1()
	, mBackgroundSprite2()
	, mStartButtonTexture(getContext().textures->get(Textures::StartButton))
	, mExitButtonTexture(getContext().textures->get(Textures::ExitButton))
	, State(stack, context)
	, mOptions()
	, mOptionIndex(0)
{
	sf::Texture& texture0 = getContext().textures->get(Textures::TitleScreen0);
	sf::Texture& texture1 = getContext().textures->get(Textures::TitleScreen1);
	sf::Texture& texture2 = getContext().textures->get(Textures::TitleScreen2);

	// Setup the start and exit buttons
	mStartButtonTexture = getContext().textures->get(Textures::StartButton);
	mExitButtonTexture = getContext().textures->get(Textures::ExitButton);
	mStartButton.setTexture(mStartButtonTexture);
	mExitButton.setTexture(mExitButtonTexture);
	mStartButton.setPosition(sf::Vector2f(context.window->getView().getSize().x / 2.f - 115.f, 380.f));
	mExitButton.setPosition(sf::Vector2f(context.window->getView().getSize().x / 2.f - 115.f, 460.f));

	sf::Font& font = context.fonts->get(Fonts::Default);

	// Construct build ID
	mBuildInfo.setFont(font);
	mBuildInfo.setCharacterSize(12);
	mBuildInfo.setPosition(sf::Vector2f(1160.f, 750.f));
	mBuildInfo.setString(Config::RELEASE_STRING);

	// Simple menu
	sf::Image playButton;
	playButton.loadFromFile("res/btn_start.png");
	
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
	window.draw(mBuildInfo);

	window.draw(mStartButton);
	window.draw(mExitButton);
}

bool MenuState::update(sf::Time dt)
{
	return true;
}

bool MenuState::isInRect(MousePosition pos, sf::Rect<float> rect)
{
	if (pos.x >= rect.left && pos.x <= rect.left+ rect.width &&
		pos.y >= rect.top && pos.y <= rect.top + rect.height)
	{
		return true;
	}

	return false;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	// Check and activate based on the mouse button click location
	MousePosition mPos = sf::Mouse::getPosition(*getContext().window);
	sf::Rect<float> startrect = sf::Rect<float>(mStartButton.getPosition().x, mStartButton.getPosition().y, 230.f, 50.f);
	sf::Rect<float> endrect = sf::Rect<float>(mExitButton.getPosition().x, mExitButton.getPosition().y, 230.f, 50.f);

	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (isInRect(mPos, startrect))
		{
			requestStackPop();
			requestStackPush(States::Loading);
		} 

		if (isInRect(mPos, endrect))
		{
			requestStackPop();
		}

	}

	if (event.type == sf::Event::MouseMoved)
	{
		if (isInRect(mPos, startrect))
		{
			mStartButton.setColor(sf::Color(255, 255, 255, 255));
		}
		else
		{
			mStartButton.setColor(sf::Color(200, 200, 200, 255));
		}
		
		if (isInRect(mPos, endrect))
		{
			mExitButton.setColor(sf::Color(255, 255, 255, 255));

		}
		else
		{
			mExitButton.setColor(sf::Color(200, 200, 200, 255));

		}
	}

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
