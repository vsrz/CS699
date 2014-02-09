
#include "DebugScreenState.h"
#include "ResourceManager.h"
#include <SFML/Window/Mouse.hpp>
#include "Glob.h"

DebugScreenState::DebugScreenState(StateStack& stack, Context context)
	: State(stack, context)
	, mDebugFps(0)
	, mDebugTime(sf::Time::Zero)
	, mMouseTime(sf::Time::Zero)
{
	
	initalizeText(mFps, sf::Vector2f(5.f, 5.f), sf::String("0 fps"));
	initalizeText(mTps, sf::Vector2f(5.f, 15.f), sf::String("0 ticks"));
	initalizeText(mMouseLabel, sf::Vector2f(5.f, 25.f), sf::String("Mouse Position:"));
	initalizeText(mMousePos, sf::Vector2f(80.f, 25.f), sf::String("0, 0"));

}

void DebugScreenState::initalizeText(sf::Text& text
	, sf::Vector2f position
	, sf::String string)
{
	sf::Font& font = getContext().fonts->get(Fonts::Default);
	text.setFont(font);
	text.setCharacterSize(12);
	text.setColor(sf::Color::White);
	text.setPosition(position);
	text.setString(string);
}

void DebugScreenState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(mFps);
	window.draw(mTps);
	window.draw(mMouseLabel);
	window.draw(mMousePos);
}

bool DebugScreenState::update(sf::Time dt)
{
	updateDebugText(dt);
	updateMouseLocation(dt);
	return true;

}

bool DebugScreenState::handleEvent(const sf::Event& event)
{
	return true;
}

void DebugScreenState::updateMouseLocation(sf::Time dt)
{
	mMouseTime += dt;

	if (mMouseTime >= sf::seconds(0.25f))
	{
		// Update this 4 times per second
		sf::Vector2i mousePos;
		sf::String posText;

		mousePos = sf::Mouse::getPosition(*getContext().window);
		posText = toString(mousePos.x);
		posText += ", ";
		posText += toString(mousePos.y);
		mMousePos.setString(posText);
		mMouseTime -= sf::seconds(0.25f);
	}

}

void DebugScreenState::updateDebugText(sf::Time dt)
{
	mDebugTime += dt;
	mDebugFps += 1;
	if (mDebugTime >= sf::seconds(1.0f))
	{
		mFps.setString(toString(mDebugFps) + " fps");
		mTps.setString(toString(mDebugTime.asMicroseconds() / mDebugFps) + " tps");
		
		mDebugTime -= sf::seconds(1.0f);
		mDebugFps = 0;
	}
}


