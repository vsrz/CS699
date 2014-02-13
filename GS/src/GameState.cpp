#include "GameState.h"
#include <iostream>
#include "Glob.h"



GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.window)
	, mPlayer(*context.player)
	, mDebugOverlay(false)
	, mClick(context.textures->get(Textures::RedClick))
{

}

void GameState::draw()
{
	mWorld.draw();
	mClick.draw(*getContext().window);
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);
	mClick.update(dt);
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);
	
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && 
		event.key.code == sf::Keyboard::Escape)
	{
		requestStackPush(States::Pause);
		return false;
	}

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

	// Left Mouse click
	else if (event.type == sf::Event::MouseButtonPressed &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// Send the click to the world to find out which tile was clicked
		sf::Vector2f pos = mWorld.getPixelPosition(sf::Mouse::getPosition(*getContext().window));
		
		mClick.addClickEvent(pos, mWorld.getWorldScale());
		//mPlayer.setDestination(sf::Vector2i(static_cast<int>(pos.x), static_cast<int>(pos.y)));
	}

	return true;
}