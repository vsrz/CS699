
#include "DebugScreenState.h"
#include "ResourceManager.h"
#include <SFML/Window/Mouse.hpp>
#include <string>
#include <map>
#include <algorithm>
#include "Glob.h"


DebugScreenState::DebugScreenState(StateStack& stack, Context context)
	: State(stack, context)
	, mDebugFps(0)
	, mDebugTime(sf::Time::Zero)
	, mMouseTime(sf::Time::Zero)

{
	extern std::map<std::string,std::string> g_debugData;	
	float yoffset = 3.f;
	float spacing = 12.f;
	initalizeText(mFps, sf::Vector2f(5.f, yoffset), sf::String("0 fps"));
	initalizeText(mTps, sf::Vector2f(5.f, yoffset + spacing), sf::String("0 u/s"));
	initalizeText(mMouseLabel, sf::Vector2f(5.f, yoffset + 2 * spacing), sf::String("Mouse Position:"));
	initalizeText(mMousePos, sf::Vector2f(95.f, yoffset + 2 * spacing), sf::String("0, 0"));
	initalizeText(mMiscInfo, sf::Vector2f(5.f, yoffset + 3 * spacing), sf::String());
}

void DebugScreenState::initalizeText(sf::Text& text
	, sf::Vector2f position
	, sf::String string)
{
	sf::Font& font = getContext().fonts->get(Fonts::Default);
	text.setFont(font);
	text.setCharacterSize(12);
	text.setColor(sf::Color::Yellow);
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
	window.draw(mMiscInfo);
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
	extern std::map<std::string, std::string> g_debugData;
	sf::String mi("");
	for (auto& iter: g_debugData)
	{
		mi += "\n" + iter.first + ": " + iter.second;
	} 
	mMiscInfo.setString(mi);
	mDebugTime += dt;
	mDebugFps += 1;
	if (mDebugTime >= sf::seconds(1.0f))
	{
		mFps.setString(toString(mDebugFps) + " fps");
		mTps.setString(toString(mDebugTime.asMicroseconds() / mDebugFps) + " u/s");
		
		mDebugTime -= sf::seconds(1.0f);
		mDebugFps = 0;
	}
}


