#ifndef STATE_H
#define STATE_H

#pragma once

#include "StateIdentifiers.h"
#include "Player.h"
#include "ResourceIdentifiers.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "ClickObject.h"
#include "ScoreGenerator.h"

namespace sf
{
	class RenderWindow;
}

class StateStack;
class ClickObject;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts, ScoreGenerator& score);
		sf::RenderWindow* window;
		TextureManager* textures;
		FontManager* fonts;
		ScoreGenerator* score;
	};

	State(StateStack& Stack, Context context);
	virtual ~State();

	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

protected:

	void requestStackPush(States::ID stateID);
	void requestStackPop();
	
	void requestStateClear();

	Context getContext() const;

private:
	StateStack* mStack;
	Context mContext;

};


#endif
