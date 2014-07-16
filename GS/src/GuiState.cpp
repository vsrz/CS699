#include "GuiState.h"


GuiState::GuiState(StateStack& stack, Context context)
	: State(stack, context)
{
	initalize();
}

void GuiState::initalize()
{
	auto window = sfg::Window::Create();
	window->SetTitle("Hello world");
	sfg::Desktop desktop;
	desktop.Add(window);
	

}

void GuiState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	window.resetGLStates();

}

bool GuiState::update(sf::Time dt)
{
	return false;
}

bool GuiState::handleEvent(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
	}
	return false;
}



