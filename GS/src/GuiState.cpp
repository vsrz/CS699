#include "GuiState.h"


GuiState::GuiState(StateStack& stack, Context context)
: State(stack, context)
{
	initalize();
}

void GuiState::initalize()
{
	mWindow = sfg::Window::Create();
	mWindow->SetTitle("Hello world");
	sfg::Desktop desktop;
	desktop.Add(mWindow);
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 0.5f);
	mButton = sfg::Button::Create("Click");
	box->Pack(mButton);
	desktop.Add(box);

}

void GuiState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.resetGLStates();
	mSfgui.Display(window);
}

bool GuiState::update(sf::Time dt)
{
	mWindow->Update(dt.asSeconds());
	return false;
}

bool GuiState::handleEvent(const sf::Event& event)
{
	if (event.key.code != sf::Event::KeyPressed)
	{
		return false;
	}
	if (event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
	}
	return false;
}



