#include "GameState.h"
#include <iostream>
#include "Glob.h"
#include "GlobalConfig.h"


GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.window, *context.textures, *context.score)
	, mDebugOverlay(false)
	, mClick(context.textures->get(Textures::RedClick), context.textures->get(Textures::GreenClick))
{

}

void GameState::draw()
{
	mWorld.draw();
	mClick.draw(*getContext().window);
}

bool GameState::update(sf::Time dt)
{
	GlobalConfig& g = GlobalConfig::get();

	mWorld.update(dt);
	mClick.update(dt);
	CommandQueue& commands = mWorld.getCommandQueue();
	if (mWorld.getScoreObject()->getTotalCustomers() >= g.TOTAL_CUSTOMERS)
	{
		requestStackPop();
		requestStackPush(States::End);
	}
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && 
		event.key.code == sf::Keyboard::Escape)
	{
		requestStackPush(States::Pause);
		return false;
	}

	else if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::F10)
	{
		requestStackPush(States::Gui);
		return false;
	}

#ifdef DEBUG
	// F3 is pressed, so bring up the debug overlay
	else if (event.type == sf::Event::KeyPressed && 
		event.key.code == sf::Keyboard::F3)
	{
		if (mDebugOverlay == false)
		{
			requestStackPush(States::Debug);
			mDebugOverlay = true;
		}
		else
		{
			requestStackPop();
			mDebugOverlay = false;
		}
		return false;
	}
#endif

	else if (event.type == sf::Event::LostFocus)
	{
#ifdef RELEASE
		requestStackPush(States::Pause);
#endif		
		return false;
	}

	// Send every other event to the world for processing
	else 		
	{
		mWorld.handleEvent(event);
	}
	
	// Left Mouse click, overlay a tile click icon
	if (event.type == sf::Event::MouseButtonPressed &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// Send the click to the world to find out which tile was clicked
		sf::Vector2i mousePos = sf::Mouse::getPosition(*getContext().window);
		
		// Remove the circle click event based on the new notification system
		//mClick.addClickEvent(snapToSpritePosition(mousePos));
	}

	return true;
}