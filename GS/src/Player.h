#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <SFML/Window.hpp>
#include <map>
#include "CommandQueue.h"
#include "Entity.h"
#include "Actor.h"
#include "Animation.h"

class Player
	: public Entity
	, public Actor
	, public Animation
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		MoveToLocation,
		ActionCount,
	};

	void assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(Action action) const;

	Player();
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);

private:
	static bool isRealtimeAction(Action action);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action,Command> mActionBinding;
	void initializeActions();

};

#endif
