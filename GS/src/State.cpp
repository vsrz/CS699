#include "State.h"

#include "State.h"
#include "StateStack.h"

State::Context::Context(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts)
	: window(&window)
	, textures(&textures)
	, fonts(&fonts)
{

}

State::State(StateStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)
{

}

State::~State()
{

}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

State::Context State::getContext() const
{
	return mContext;
}

void State::requestStateClear()
{
	mStack->clearStates();
}

